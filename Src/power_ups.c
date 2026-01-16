/*
 * power_ups.c
 *
 *  Created on: 15. jan. 2026
 *      Author: anna2
 */

#include "power_ups.h"

static const char *medkit_sprite[] = {
    " + ",
    "+++",
    " + "
};
static const char *shield_sprite[] = {
    " /\\",
    "|##|",
    " \\/"
};
static const char *multibullet_sprite[] = {
    "| |",
    "| |",
    "| |"
};


void init_powerup(powerup *pu){
	pu->active = 0;
	pu->type = PU_NONE;
	pu->lifetime = 0;
}

void init_all_powerups(powerup *pus){
	//initialiserer alle powerups til ikke at eksistere endnu
	for(int i = 0; i < MAX_POWERUPS; i++){
		init_powerup(&pus[i]);
	}
}

void spawn_powerup(powerup *pu, powerup_type type, uint16_t x, uint16_t y){
	pu->x = x;
	pu->y = y;
	pu->type = type;
	pu->active = 1;
	pu->lifetime = 0;
}

void update_powerup(powerup *pu, player *p){
	if(!pu->active){
		return;
	}
	pu->old_x = pu->x;
	pu->old_y = pu->y;

	pu->lifetime++;

	if(pu->lifetime>=1000){ //10 sek
		erase_powerup(pu);
		deactivate_powerup(pu);
		return;
	}

	/*----------- collision - ethvert overlap ------------*/
	//player bounds
	int p_left = p->x;
	int p_right = p->x + 8 - 1;
	int p_top = p->y;
	int p_bottom = p->y + 6 - 1;
	//powerup bounds
	int pu_left = pu->x;
	int pu_right = pu->x + 3 - 1;
	if(pu->type == PU_SHIELD){
		pu_right = pu->x + 4 - 1;
	}
	int pu_top = pu->y;
	int pu_bottom = pu->y + 3 - 1;
	//overlap check
	if(p_left <= pu_right && p_right >= pu_left && p_top <= pu_bottom && p_bottom >= pu_top){
		erase_powerup(pu);
		apply_powerup(pu, p);
		deactivate_powerup(pu);
	}

}

void draw_powerup(const powerup *pu){
	if(!pu->active){
		return;
	}

	gotoxy(pu->x, pu->y);
	switch(pu->type){
	case PU_MEDKIT:
		fgcolor(1);
		for(int i = 0; i < 3; i++){
			gotoxy(pu->x, pu->y + i);
			printf("%s", medkit_sprite[i]);
		}
		break;
	case PU_SHIELD:
		fgcolor(6);
		for(int i = 0; i < 3; i++){
			gotoxy(pu->x, pu->y + i);
			printf("%s", shield_sprite[i]);
		}
		break;
	case PU_MULTI_BULLET:
		fgcolor(3);
		for(int i = 0; i < 3; i++){
			gotoxy(pu->x, pu->y + i);
			printf("%s", multibullet_sprite[i]);
		}
		break;
	default:
		break;
	}
}

void apply_powerup(powerup *pu, player *p){
	switch(pu->type){
	case PU_MEDKIT:
		p->hp+=1;
		break;
	case PU_SHIELD:
		p->shield_active = 1;
		p->shield_timer = 0;
		break;
	case PU_MULTI_BULLET:
		//senere
		break;
	default:
		break;
	}
}

void deactivate_powerup(powerup *pu){
	pu->active = 0;
	pu->type = PU_NONE;
	pu->lifetime = 0;
}

void erase_powerup(powerup *pu){
	//skal senere opdatere vinduet i stedet
	int width = 3;
	if(pu->type == PU_SHIELD){
		width = 4;
	}

	for(int i = 0; i < 3; i++){
		gotoxy(pu->old_x, pu->old_y + i);// + i gør den rykker ned til næste linje (det er en 3x3)
		for(int j = 0; j < width;j++){
			printf("   ");
		}
	}
}


powerup *get_available_powerup(powerup *pus){
	for(int i = 0; i < MAX_POWERUPS;i++){
		if(!pus[i].active){
			return &pus[i];
		}
	}
	return NULL;
}

void spawn_random_powerup(powerup *pus){
	powerup *pu = get_available_powerup(pus);
	if(!pu) return; //ingen ledige powerups tilbage, burde ikke ske

	powerup_type type;

	int r = rand() % 3;
	if(r == 0) type = PU_MEDKIT;
	else if(r == 1) type = PU_SHIELD;
	else type = PU_MULTI_BULLET;

	// bredde afhængigt af type
	int width = (type == PU_SHIELD) ? 4 : 3;
	int height = 3;

	int x = (rand() % (GAME_WIDTH  - width  - 2)) + 2;
	int y = (rand() % (GAME_HEIGHT - height - 2)) + 2;

	spawn_powerup(pu, type, x, y);
}
