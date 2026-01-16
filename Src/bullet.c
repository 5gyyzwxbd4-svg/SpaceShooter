/*
 * bullet.c
 *
 *  Created on: 14. jan. 2026
 *      Author: alex
 */

#include "ansi.h"
#include "bullet.h"
#include <stdio.h>
#include <stdint.h>
#include "player.h"
#include "astroids.h"

// initialiserer max antal bullets i et array, som alle er inaktive.
void init_bullet_pool(bullet bullets[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        bullets[i].active = 0;
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].dx = 0;
        bullets[i].dy = 0;
    }
}

// funktionen "affyrerer" et skud.
void fire_bullet(bullet bullets[], int size, player *p) {
    int i;

    for (i = 0; i < size; i++) {
        if (bullets[i].active == 0) {
            bullets[i].active = 1;
            bullets[i].x = p->x + 1;
            bullets[i].y = p->y - 5;
            bullets[i].dx = 1;
            bullets[i].dy = 0;
            break;
        }
    }
}

// opdaterer lokationen af alle bullets.
void update_bullets(bullet bullets[], int size, astroid *a, astroid_bound *ab) {
    uint8_t i;
    fgcolor(9);

    for (i = 0; i < size; i++) {


        if (bullets[i].active) {
        	//sletter gamle bullet lokation
            gotoxy(bullets[i].x, bullets[i].y);
            printf(" ");

            //opdaterer bullet lokation
            bullets[i].x += bullets[i].dx;
            bullets[i].y += bullets[i].dy;

            //tjekker kollision med vægge eller asteroide
            if ((bullets[i].x > 150) || (bullets[i].y > 45) || (bullets[i].y < 1) ||
               ( (bullets[i].x > (a->x)) && (bullets[i].x < (a->x+28)) && (bullets[i].y > (a->y)) && (bullets[i].y < (a->y+13)) )  ) {

                bullets[i].active = 0;

            } else {
                //tegner bullet ved ny lokation, hvis der IKKE er kollision.
                gotoxy(bullets[i].x, bullets[i].y);
                printf("o");

                //adskilder asteroiden i to halve - øvre halvdel og nedre halvdel
                uint16_t center_y = (ab->y_min + ab->y_max) >> 1;

                if ((bullets[i].x > ab->x_min) && (bullets[i].x < ab->x_max) && (bullets[i].y > ab->y_min) && (bullets[i].y < ab->y_max)) {
                    if (bullets[i].y < center_y) {
                        if (bullets[i].dy < 3) {
                            bullets[i].dy++;
                        }
                    }
					if (bullets[i].y > center_y) {
						if (bullets[i].dy > -3) {
							bullets[i].dy--;
						}
                    }
                }
            }
        }
    }

    fgcolor(15);
}
