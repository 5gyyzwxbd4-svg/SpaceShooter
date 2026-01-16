/*
 * bullet.h
 *
 *  Created on: 14. jan. 2026
 *      Author: root
 */

#ifndef BULLET_H_
#define BULLET_H_
#include "player.h"
#include "astroids.h"


#define MAX_BULLETS 20 // The maximum number of bullets on screen at once

typedef struct {
    int32_t x, y;
    int32_t dx, dy;
    uint8_t active;   // 1 = flying, 0 = ready to be fired
} bullet;

// Function prototypes
void init_bullet_pool(bullet bullets[], int size);
void fire_bullet(bullet bullets[], int size, player *p);
void update_bullets(bullet bullets[], int size, astroid *a, astroid_bound *ab);

#endif /* BULLET_H_ */
