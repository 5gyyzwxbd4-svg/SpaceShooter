/*
 * timer.h
 *
 *  Created on: 14. jan. 2026
 *      Author: Alex
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>


void timer15_init(); // timer funktion
void TIM1_BRK_TIM15_IRQHandler(void); // interrupts funktion

extern volatile uint16_t tick_10ms;     // stiger 1 i værdi hvert 10 ms. -- GLOBAL VARIABEL
extern volatile uint8_t  flag_10ms;    // skal sættes til 1 hvert 10. ms. -- GLOBAL VARIABEL



#endif /* TIMER_H_ */
