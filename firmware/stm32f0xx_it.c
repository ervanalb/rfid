#include "stm32f0xx_it.h"
#include "stm32f0xx.h"
#include "hal.h"
#include "usb_dcd_int.h"

#define LATENCY 120

uint16_t reading;

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
}

void EXTI0_1_IRQHandler() {
    TIM1->CNT = LATENCY;
    EXTI->PR = EXTI_Line1;
}

void TIM1_BRK_UP_TRG_COM_IRQHandler() {
    ADC1->CR |= (uint32_t)ADC_CR_ADSTART;
    TIM1->SR = ~TIM_IT_Update;
}

void USB_IRQHandler() {
    USB_Istr();
}
