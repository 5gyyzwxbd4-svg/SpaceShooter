/*
 * adc.h
 *
 *  Created on: 14. jan. 2026
 *      Author: fueke
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);
uint16_t adc_read_channel(uint8_t channel); // 1=PA0, 2=PA1


#endif /* ADC_H_ */
