/*
 * astroids.c
 *
 *  Created on: 13. jan. 2026
 *      Author: Alex
 */

#include "ansi.h"
#include "astroids.h"
#include <stdio.h>
#include <stdint.h>
#include "player.h"

void init_astroid(astroid *a, astroid_bound *ab) {

	a->x = 122;
	a->y = 30;

	ab->x_min = a->x-10;
	ab->x_max = a->x+38;
	ab->y_min = a->y-10;
	ab->y_max = a->y+22;


}

void move_astroid(astroid *a, astroid_bound *ab, player *p) {
	// funktionen starter med at fjerne asteroiden på dens nuværende lokation og printer
	// derefter en ny asteroide til højre.
	fgcolor(7);


	const char *astroide[] = {
	        "      .:-+*#*++==++-:.",
	        "   :+%#**=++----=***%*+.",
	        "  *%*+##*=---=+=--++++=:.",
	        " *++%#++*-+=+-:.::..:=::.:",
	        "++*+*+=+***--::.:....--=-::",
	        "%*==+*+=*-:::-:......==-:::.",
	        ":#=+=-......:::....::%*-::.:",
	        " +*=-=:......:=-.::::-::::::",
	        "  *==+=......+-+=::::::::.:.",
	        "   =#++:-:=-#=+-=:::::::::",
	        "    .-=:...:-::..:::::::",
	        "      .=::--::--::::::",
	        "        ..:--:---:."
	    };
	int lines = sizeof(astroide) / sizeof(astroide[0]);

			for (int i = 0; i < lines; i++) {
			    gotoxy(a->x, a->y+i);
			    printf("\x1b[K");
			    }


			for (int i = 0; i < lines; i++) {
			    gotoxy(a->x,a->y+i);
			    printf("%s", astroide[i]);


			    }
			if ((a->x)>1) {
				a->x--;
				ab->x_min--;
				ab->x_max--;
			}else {
				for (int i = 0; i < lines; i++) {
				gotoxy(a->x, a->y+i);
				printf("\x1b[K");

				}
				a->x = 122;
				ab->x_min = a->x-20;
				ab->x_max = a->x+48;
			}
	fgcolor(15);
	}
