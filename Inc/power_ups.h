/*
 * power_ups.h
 *
 *  Created on: 15. jan. 2026
 *      Author: anna2
 */

#ifndef POWER_UPS_H_
#define POWER_UPS_H_

#include "player.h"
#include "ansi.h"

#define MAX_POWERUPS 32
#define GAME_WIDTH   150
#define GAME_HEIGHT  45

typedef enum{
	PU_NONE,
	PU_MEDKIT,
	PU_SHIELD,
	PU_MULTI_BULLET
}powerup_type;

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t old_x;
	uint16_t old_y;
	uint8_t active; //0 = findes ikke, 1 = på skærmen
	uint16_t lifetime; //definerer hvor lang tid den er tilstede
	powerup_type type; //enum -> hvilken type power up det er
}powerup;

void init_powerup(powerup *pu);
void init_all_powerups(powerup *pus);
void spawn_powerup(powerup *pu, powerup_type type, uint16_t x, uint16_t y);
void update_powerup(powerup *pu, player *p);
void draw_powerup(const powerup *pu);
void apply_powerup(powerup *pu, player *p);
void deactivate_powerup(powerup *pu);
void erase_powerup(powerup *pu);

powerup *get_available_powerup(powerup *pus);
void spawn_random_powerup(powerup *pus);

#endif /* POWER_UPS_H_ */
