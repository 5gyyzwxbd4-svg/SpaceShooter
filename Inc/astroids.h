/*
 * Astroide.h
 *
 *  Created on: 13. jan. 2026
 *      Author: root
 */

#ifndef ASTROIDS_H_
#define ASTROIDS_H_
#include "player.h"

typedef struct{
		int16_t x;
		int16_t y;
}astroid;

typedef struct{
		int16_t x_min;
		int16_t x_max;
		int16_t y_min;
		int16_t y_max;
}astroid_bound;


void init_astroid(astroid *a, astroid_bound *ab);
void move_astroid(astroid *a, astroid_bound *ab, player *p);



#endif /* ASTROIDS_H_ */
