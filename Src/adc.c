/*
 * adc.c
 *
 *  Created on: 14. jan. 2026
 *      Author: fueke
 */


#include "stm32f30x_conf.h"
#include "adc.h"
#include <stdint.h>

static void gpioa_init_for_adc_inputs(void)
{
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

    /* PA0 input */
    GPIOA->MODER &= ~(3U << (0 * 2));
    GPIOA->PUPDR &= ~(3U << (0 * 2));   // no pull

    /* PA1 input */
    GPIOA->MODER &= ~(3U << (1 * 2));
    GPIOA->PUPDR &= ~(3U << (1 * 2));   // no pull
}

void adc_init(void)
{
    gpioa_init_for_adc_inputs();

    /* ADC12 clock prescaler: DIV6 (64/6=10.67MHz < 30MHz) */
    RCC->CFGR2 &= ~RCC_CFGR2_ADCPRE12;
    RCC->CFGR2 |= RCC_CFGR2_ADCPRE12_DIV6;

    /* Enable ADC12 clock */
    RCC->AHBENR |= RCC_AHBPeriph_ADC12;

    /* Reset ADC1 config to standard mode */
    ADC1->CR = 0x00000000;
    ADC1->CFGR &= 0xFDFFC007;
    ADC1->SQR1 &= ~ADC_SQR1_L;

    /* Enable internal regulator */
    ADC1->CR |= 0x10000000;
    for (volatile int i = 0; i < 1000; i++) {}

    /* Calibrate */
    ADC1->CR |= 0x80000000;
    while (ADC1->CR & 0x80000000) {}
    for (volatile int i = 0; i < 100; i++) {}

    /* Enable ADC */
    ADC1->CR |= 0x00000001;
    while (!(ADC1->ISR & 0x00000001)) {}
}

uint16_t adc_read_channel(uint8_t channel)
{
    /* channel: 1=PA0, 2=PA1 */
    if (channel == 1) {
        ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_1Cycles5);
    } else if (channel == 2) {
        ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_1Cycles5);
    } else {
        return 0;
    }

    ADC_StartConversion(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == 0) {}

    return ADC_GetConversionValue(ADC1);
}


