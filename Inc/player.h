/*
 * player.h
 *
 *  Created on: 15. jan. 2026
 *      Author: anna2
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x_conf.h"
#include "ansi.h"

#define PLAYER_WIDTH  8
#define PLAYER_HEIGHT 6

typedef struct{
	uint16_t x, y;
	uint16_t old_x, old_y;
	uint16_t vx, vy;
	uint16_t hp;
	uint16_t score;

	uint8_t shield_active;
	uint16_t shield_timer;
	uint8_t shield_just_ended;
}player;

//joystick
void adc_init();
uint16_t adc_read_channel(uint8_t channel);

//player
void init_player(player *p); //initialiser spilleren
void draw_player(player *p); //tegn spilleren
uint16_t update_player(player *p); //opdater spillerens position hvis positionen har ændret sig
uint16_t move_player(player *p); //bevæg spilleren baseret på joystick
void keep_player_in_game(player *p); //sørg for spilleren ikke bevæger sig ud for billedet
void take_damage_player(player *p);
void erase_player(player *p);
void reset_player(player *p);


#endif /* PLAYER_H_ */
