/*
 * player.h
 *
 *  Created on: 15. jan. 2026
 *      Author: anna2
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <stdint.h>


typedef struct{
	int16_t x, y;
	int16_t vx, vy;
	int16_t hp;
	int16_t score;
}player;

//joystick
void adc_init();
uint16_t adc_read_channel(uint8_t channel);

//player
void init_player(player *p);
void draw_player(player *p);
void update_player(player *p);
void move_player(player *p);
void keep_player_in_game(player *p);
void take_damage_player(player *p);
void reset_player(player *p);


#endif /* PLAYER_H_ */
