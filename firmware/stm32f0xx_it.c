#include "stm32f0xx_it.h"
#include "stm32f0xx.h"
#include "hal.h"
#include "usb_dcd_int.h"

#define LATENCY 75

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

void USB_IRQHandler() {
    USB_Istr();
}

void DMA1_Channel1_IRQHandler() {
}
