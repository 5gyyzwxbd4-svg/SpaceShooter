/*
 * timer.c
 *
 *  Created on: 14. jan. 2026
 *      Author: Alex
 */


#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include <stdint.h>
#include <stdio.h>
#include "timer.h"


volatile uint16_t tick_10ms = 0;     // stiger 1 i værdi hvert 10 ms. -- GLOBAL VARIABEL
volatile uint8_t  flag_10ms  = 0;    // skal sættes til 1 hvert 10. ms. -- GLOBAL VARIABEL

void timer15_init()
{
    //funktionen aktiverer en 100hz (10ms) timer
	// 1) Enable TIM15 peripheral clock
    RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;

    uint32_t psc = (64000000U / 1000U) - 1U;
    uint32_t arr = 10U - 1U;

    TIM15->CR1 = 0;
    TIM15->PSC = (uint16_t)psc;
    TIM15->ARR = (uint16_t)arr;


    TIM15->EGR = TIM_EGR_UG;
    TIM15->SR  = 0;

    // 4) Enable update interrupt
    TIM15->DIER |= TIM_DIER_UIE;

    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);

    // 6) Enable global interrupts
    __enable_irq();

    // starter counter
    TIM15->CR1 |= TIM_CR1_CEN;
}


void TIM1_BRK_TIM15_IRQHandler(void) {

	//kode for interrupt

	tick_10ms++;
	flag_10ms = 1;

	TIM15->SR &= ~0x0001; // Clear interrupt bit

}
