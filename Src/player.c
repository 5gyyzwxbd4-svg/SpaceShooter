/*
 * player.c
 *
 *  Created on: 15. jan. 2026
 *      Author: anna2
 */

#include "player.h"

//----------------INIT----------------------
void init_player(player *p){
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
	/*----------- shield powerup --------------*/
	if(p->shield_active){
		fgcolor(6);

		//top
		gotoxy(p->x - 1, p->y - 1);
		printf(" --------- ");

		//sider
		for(int i = 0; i < 6; i++){
			gotoxy(p->x - 2, p->y + i);
			printf("|");
			gotoxy(p->x + 8, p->y + i);
			printf("|");
		}

		//bund
		gotoxy(p->x - 1, p->y + 6);
		printf(" --------- ");
	}

	/* ---------- spiller ----------------*/
	gotoxy(p->x, p->y);
	fgcolor(11);
	const char *space_ship[] = {
	    "  -+:   ",
	    "  :+.   ",
	    "-=++-+*=",
	    "-=++-+*=",
	    "  :+.   ",
	    "  -+:   "
	};
	for(int i = 0; i < 6; i++){
	    gotoxy(p->x, p->y + i);
	    printf("%s", space_ship[i]);
	}
	resetbgcolor();
}

uint16_t update_player(player *p){
	static uint8_t move_tick = 0; //tæller antal 10 ms ticks
	int moved = 0;

	p->old_x = p->x;
	p->old_y = p->y;

	take_damage_player(p);
	p->shield_just_ended = 0;
	if(p->shield_active){
		p->shield_timer++;
		if(p->shield_timer >= 1500){
			p->shield_active = 0; //skal deaktiveres efter 15 sekunder
			p->shield_just_ended = 1;
		}
	}

	move_tick++;
	if (move_tick >= 8){ //sørger for den kun opdateres hvert 80 ms
		move_tick = 0;
		moved = move_player(p);
		keep_player_in_game(p);
	}

	return moved;
}

uint16_t move_player(player *p){
	int moved = 0;
	uint16_t joy_x = adc_read_channel(1); // PA0 (ADC1_IN1, left/right)
	uint16_t joy_y = adc_read_channel(2); // PA1 (ADC1_IN2, up/down)

	//right/left
	if (joy_x > 1325){
		p->x += 1; //1=speed lige nu
		moved = 1;
	}else if(joy_x<1025){
		p->x -= 1;
		moved = 1;
	}

	//down/up
	if(joy_y<10){
		p->y += 1;
		moved = 1;
	}else if(joy_y>30){
		p->y -= 1;
		moved = 1;
	}
	return moved;
}

void keep_player_in_game(player *p){
	//mangler værdier for størrelse af vindue

	// Midlertidige testværdier
	const int MIN_X = 1;
	const int MIN_Y = 1;
	const int MAX_X = 130-8;
	const int MAX_Y = 40-6;

	if (p->x < MIN_X) p->x = MIN_X;
	if (p->x > MAX_X) p->x = MAX_X;
	if (p->y < MIN_Y) p->y = MIN_Y;
	if (p->y > MAX_Y) p->y = MAX_Y;
}

void take_damage_player(player *p){
	//hvis ramt af asteroide
	//hvis ramt af enemy
	//hvis enemy forlader skærmen (de smadrer hjembyen!!)

	/*if(1/*ramt af asteroid/enemy){
		if(p->shield_active){
			p->shield_active = 0;
			return;
		}
		p->hp--;
	}*/

	if (p->hp<0){
		//game over
		reset_player(p);
	}
}

void erase_player(player *p)
{
	if (p->shield_active || p->shield_just_ended){
		// slet hele shield + spiller
		for (int i = -1; i <= 6; i++) {
			gotoxy(p->old_x - 2, p->old_y + i);
			printf("            "); // 12 mellemrum
		}
	}else{
		// slet kun spilleren
		for (int i = 0; i < 6; i++){
			gotoxy(p->old_x, p->old_y + i);
			printf("        "); // 8 mellemrum
		}
	}
}


void reset_player(player *p){
	init_player(p);
}
