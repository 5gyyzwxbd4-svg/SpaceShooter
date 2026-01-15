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



void spawn_astroids(void) {
	// funktionen printer en simpel astroide.
	gotoxy(100,10);
	const char *astroide[] = {
        "            .:-+*#*++==++-:.",
        "         :+%#**=++----=***%*+.",
        "        *%*+##*=---=+=--++++=:.",
        "       *++%#++*-+=+-:.::..:=::.:",
        "      ++*+*+=+***--::.:....--=-::",
        "      %*==+*+=*-:::-:......==-:::.",
        "      :#=+=-......:::....::%*-::.:",
        "       +*=-=:......:=-.::::-::::::",
        "        *==+=......+-+=::::::::.:.",
        "         =#++:-:=-#=+-=:::::::::",
        "          .-=:...:-::..:::::::",
        "            .=::--::--::::::",
        "              ..:--:---:."
    };

    int lines = sizeof(astroide) / sizeof(astroide[0]);
    for (int i = 0; i < lines; i++) {
        gotoxy(100,10+i);
    	printf("%s\n", astroide[i]);
    }
}

void move_astroids(int16_t x, int8_t stop) {
	// funktionen starter med at fjerne astroiden på dens nuværende lokation og printer
	// derefter en ny astroide til højre.

	gotoxy(x,10);
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
			        gotoxy(x-1, 10+i);
			    	printf("                                   ");
			    }

			    for (int i = 0; i < lines; i++) {
			        gotoxy(x-1,10+i);
			    	printf("%s\n", astroide[i]);


			    }
	if (stop) {
		for (int i = 0; i < lines; i++) {
			gotoxy(x, 10+i);
			printf("                                   ");
					    }
	}




}

