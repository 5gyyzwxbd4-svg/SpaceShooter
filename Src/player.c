/*
 * player.c
 *
 *  Created on: 15. jan. 2026
 *      Author: anna2
 */

#include "player.h"

//----------------INIT----------------------
void init_player(player *p){
	adc_init();

	p->x = 1;
	p->y = 25;
	p->hp = 3;
	p->score = 0;
}

static void gpioa_init_for_adc_inputs(void){
    RCC->AHBENR |= RCC_AHBPeriph_GPIOA;

    /* PA0 input */
    GPIOA->MODER &= ~(3U << (0 * 2));
    GPIOA->PUPDR &= ~(3U << (0 * 2));   // no pull

    /* PA1 input */
    GPIOA->MODER &= ~(3U << (1 * 2));
    GPIOA->PUPDR &= ~(3U << (1 * 2));   // no pull
}

void adc_init(){
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

uint16_t adc_read_channel(uint8_t channel){
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

//---------------update--------------

void draw_player(player *p){
	//
}

void update_player(player *p){
	move_player(p);
	take_damage_player(p);
	keep_player_in_game(p);
}

void move_player(player *p){
	//joystick=analoge spændinger i x og y (læs med adc)
	//PA0 = x (ADC1_IN1 - left/right)
	//PA1 = y (ADC1_IN2 - up/down)
	uint16_t joy_x = adc_read_channel(1); // PA0
	uint16_t joy_y = adc_read_channel(2); // PA1

	//right/left
	if (joy_x > 2300){
		p->x += 1; //1=speed lige nu
	}else if(joy_x<1800){
		p->x -= 1;
	}

	//down/up
	if(joy_y<1800){
		p->y += 1;
	}else if(joy_y>2300){
		p->y -= 1;
	}

}

void keep_player_in_game(player *p){

}

void take_damage_player(player *p){
	//hvis ramt af asteroide
	//hvis ramt af enemy
	//hvis enemy forlader skærmen (de smadrer hjembyen!!)
	if (hp<0){
		//game over
		reset_player(p);
	}

}

void reset_player(player *p){
	init_player(p);
}
