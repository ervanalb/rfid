#include "stm32f0xx.h"
#include "hal.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_class.h"
#include "usbd_usr.h"
#include <string.h>

#define DEFAULT_LATENCY 230
#define PERIOD 384

#define RX_BUFFER_SIZE 512
#define TX_BUFFER_SIZE 512

// Buffer where samples read from the card are put
static volatile int16_t rx_buffer[RX_BUFFER_SIZE];

// Buffer where samples written to the card are put
static volatile int8_t tx_buffer[TX_BUFFER_SIZE];

// Pointer to buffer where data is being read (lags DMA counter)
static volatile int rx_read_ptr = 0;

// Pointer to buffer where data is being read (lags write pointer)
static volatile int tx_read_ptr = TX_BUFFER_SIZE;

// Pointer to buffer where data is being written (leads output pointer)
static volatile int16_t tx_write_ptr = 0;

// Whether we are streaming
volatile int stream_read_enabled = 0;
volatile int stream_write_enabled = 0;

static volatile int16_t latency = DEFAULT_LATENCY;

USB_CORE_HANDLE  USB_Device_dev;

volatile int led_timer;
volatile int button_timer;

// Bring up all hardware
void init() {
    GPIO_InitTypeDef GPIO_InitStruct;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;
    ADC_InitTypeDef ADC_InitStruct;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOF |
                          RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG | RCC_APB2Periph_ADC1 |
                           RCC_APB2Periph_TIM1, ENABLE);

    // SysTick
    SysTick_Config(SystemCoreClock / 1000); // Fires every 1ms
    NVIC_SetPriority(SysTick_IRQn, 1);

    // LEDs
    led_read_off();
    led_write_off();
    led_spoof_off();
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOF, &GPIO_InitStruct);

    // Button
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Coil drive
    TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = PERIOD - 1;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStruct.TIM_Pulse = PERIOD / 2 - 1;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(TIM14, &TIM_OCInitStruct);
    TIM_CtrlPWMOutputs(TIM14, ENABLE);
    TIM_Cmd(TIM14, ENABLE);
    coil_float();

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_0);

    // Coil detune
    coil_tune();
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // SD Card
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 |  GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_0);

    GPIOA->BSRR = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // ADC Read Timer
    TIM_TimeBaseInitStruct.TIM_Prescaler = 0;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = PERIOD - 1;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStruct.TIM_Pulse = PERIOD / 2 - 1;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(TIM1, &TIM_OCInitStruct);
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_OC1);
    TIM_Cmd(TIM1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
    // TODO make sure this interrupt doesn't crash into EXTI too often
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Coil analog
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // ADC
    ADC_DeInit(ADC1);
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_TRGO;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStruct);
    ADC_ChannelConfig(ADC1, ADC_Channel_2, ADC_SampleTime_1_5Cycles);

    // ADC DMA
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_BufferSize = RX_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)rx_buffer;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Low;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC | DMA_IT_HT, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x02;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ADC final bringup
    ADC_GetCalibrationFactor(ADC1);
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY));
    ADC_StartOfConversion(ADC1);

    // Coil digital
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);
  
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  
    // USB
    SYSCFG->CFGR1 |= 1 << 4; // PA11_PA12_RMP
    USBD_Init(&USB_Device_dev, &USR_desc,
              &USBD_custom_cb, &USR_cb);

    stream_read_disable();
    stream_write_disable();
}

void led_read_off() {GPIOA->BRR = GPIO_Pin_0;}
void led_read_on() {GPIOA->BSRR = GPIO_Pin_0;}

void led_write_off() {GPIOF->BRR = GPIO_Pin_1;}
void led_write_on() {GPIOF->BSRR = GPIO_Pin_1;}

void led_spoof_off() {GPIOF->BRR = GPIO_Pin_0;}
void led_spoof_on() {GPIOF->BSRR = GPIO_Pin_0;}

int button() {return (GPIO_ReadInputData(GPIOB) & GPIO_Pin_8) == GPIO_Pin_8;}

void coil_drive() {TIM14->CCER |= TIM_OutputState_Enable;}
void coil_float() {TIM14->CCER &= ~TIM_OutputState_Enable;}

void coil_tune() {GPIOA->BSRR = GPIO_Pin_3;}
void coil_detune() {GPIOA->BRR = GPIO_Pin_3;}

static void sd_set_cs_high() {
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY));
    GPIOA->BSRR = GPIO_Pin_4;
}

static void sd_set_cs_low() {
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY));
    GPIOA->BRR = GPIO_Pin_4;
}

static void sd_write_byte(uint8_t byte) {
    SPI_SendData8(SPI1, byte);
    while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE));
}

static uint8_t sd_read_response() {
    uint16_t timeout;
    uint8_t response;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY));
    SPI_ReceiveData8(SPI1);

    timeout = SD_TIMEOUT;
    while(timeout--)
    {
        SPI_SendData8(SPI1, 0xFF);
        while(!SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE));
        response = SPI_ReceiveData8(SPI1);
        if(response != 0xFF) break;
    }
    return response;
}

int sd_init() {
    SPI_InitTypeDef SPI_InitStruct;

    SPI_I2S_DeInit(SPI1);
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;

    SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 375 KHz
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1,&SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);

    // Leave CS high
    for(int i = 0; i < 10; i++) // Apply 80 clock pulses
    {
        sd_write_byte(0xFF);
    }

    sd_set_cs_low();

    sd_write_byte(0x40);
    sd_write_byte(0x00);
    sd_write_byte(0x00);
    sd_write_byte(0x00);
    sd_write_byte(0x00);
    sd_write_byte(0x95);

    uint8_t r;
    r = sd_read_response();

    sd_set_cs_high();

    if(r == 0xFF) return -1; // Timeout
    if(r != 0x01) return -2; // Card error

    SPI_I2S_DeInit(SPI1);
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; // 12 MHz
    SPI_Init(SPI1,&SPI_InitStruct);
    SPI_Cmd(SPI1, ENABLE);

    return 0;
}

// These commands control whether data flows from the coil into memory
void stream_read_enable() {
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, RX_BUFFER_SIZE);
    rx_read_ptr = 0;
    DMA_Cmd(DMA1_Channel1, ENABLE);
    stream_read_enabled = 1;
}

void stream_read_disable() {
    DMA_Cmd(DMA1_Channel1, DISABLE);
    stream_read_enabled = 0;
}

// These commands control whether data flows from memory into the coil
void stream_write_enable() {
    TIM_ITConfig(TIM14, TIM_IT_Update, DISABLE);
    tx_read_ptr = 0;
    stream_write_enabled = 1;
    TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
}

void stream_write_disable() {
    TIM_ITConfig(TIM14, TIM_IT_Update, DISABLE);
    stream_write_enabled = 0;
    memset((void*)tx_buffer, 1, TX_BUFFER_SIZE);
    tx_read_ptr = TX_BUFFER_SIZE;
    tx_write_ptr = 0;
}

// Calculate the number of halfwords behind the DMA counter the read pointer currently is.
// Assume no overflows.
int stream_read_available() {
    int remaining = RX_BUFFER_SIZE - DMA_GetCurrDataCounter(DMA1_Channel1) - rx_read_ptr;
    if(remaining < 0) remaining += RX_BUFFER_SIZE;
    return remaining;
}

// Read n samples from rx buffer into samples
void stream_read(int16_t* samples, int n) {
    for(int i = 0; i < n; i++) {
        samples[i] = rx_buffer[rx_read_ptr];
        rx_read_ptr = (rx_read_ptr + 1) % RX_BUFFER_SIZE;
    }
}

// Returns the maximum number of samples that can be written to the tx buffer.
// Assumes no overflows.
int stream_write_space() {
    int available = tx_read_ptr - tx_write_ptr;
    if(available < 0) available += TX_BUFFER_SIZE;
    return available;
}

// Write n bytes into the tx buffer
void stream_write(int8_t *samples, int n) {
    for(int i=0; i<n; i++) {
        tx_buffer[tx_write_ptr] = samples[i];
        tx_write_ptr = (tx_write_ptr + 1) % TX_BUFFER_SIZE;
    }
}

// Write 1 byte into the tx buffer
void stream_write_byte(int8_t byte) {
    tx_buffer[tx_write_ptr] = byte;
    tx_write_ptr = (tx_write_ptr + 1) % TX_BUFFER_SIZE;
}

void set_latency(int16_t l) {
    latency = l;
}

// INTERRUPTS

void NMI_Handler() {
}

void HardFault_Handler() {
    for(;;);
}

void SVC_Handler() {
}

void PendSV_Handler() {
}

void SysTick_Handler() {
    if(led_timer > 0) led_timer--;
    if(button_timer > 0) button_timer--;
}

void EXTI0_1_IRQHandler() {
    TIM1->CNT = latency;
    EXTI->PR = EXTI_Line1;
}

void TIM14_IRQHandler() {
    TIM14->SR = (uint16_t)~TIM_IT_Update;
    if(tx_buffer[tx_read_ptr]) {
        coil_tune();
        coil_drive();
    } else {
        coil_float();
        coil_detune();
    }
    tx_buffer[tx_read_ptr] = 1;
    tx_read_ptr = (tx_read_ptr + 1) % TX_BUFFER_SIZE;
}

void USB_IRQHandler() {
    USB_Istr();
}

void DMA1_Channel1_IRQHandler() {
    DMA_ClearITPendingBit(DMA1_IT_TC1 | DMA1_IT_HT1);
}
