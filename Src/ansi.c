/*
 * ansi.c
 *
 *  Created on: 13. jan. 2026
 *      Author: root
 */
#include "ansi.h"
#include <stdio.h>
#include <stdint.h>

// changes color of characters in terminal
void fgcolor(uint8_t foreground) {
    /*  Value      foreground     Value     foreground
        ------------------------------------------------
          0        Black            8       Dark Gray
          1        Red              9       Light Red
          2        Green           10       Light Green
          3        Brown           11       Yellow
          4        Blue            12       Light Blue
          5        Purple          13       Light Purple
          6        Cyan            14       Light Cyan
          7        Light Gray      15       White
    */
    uint8_t type = 22; // normal text
    if (foreground > 7) {
        type = 1;      // bold text
        foreground -= 8;
    }
    printf("%c[%d;%dm", ESC, type, (int)foreground + 30);
}

// change background color in terminal
void bgcolor(uint8_t background) {
    /* Value      Color
       ------------------
         0        Black
         1        Red
         2        Green
         3        Brown
         4        Blue
         5        Purple
         6        Cyan
         7        Gray
    */
    printf("%c[%dm", ESC, (int)background + 40);
}

void color(uint8_t foreground, uint8_t background) {
    // combination of fgcolor() and bgcolor() - uses less bandwidth
    uint8_t type = 22; // normal text
    if (foreground > 7) {
        type = 1;      // bold text
        foreground -= 8;
    }
    printf("%c[%d;%d;%dm", ESC, type, (int)foreground + 30, (int)background + 40);
}

void resetbgcolor(void) {
    // reset all attributes
    printf("%c[0m", ESC);
}

void clrscr(void) {
    // clear screen + cursor home
    printf("%c[2J%c[H", ESC, ESC);
}

void clreol(void) {
    // clear to end of line
    printf("%c[K", ESC);
}

void gotoxy(uint8_t x, uint8_t y) {
    // move cursor to position (x,y)
    printf("%c[%d;%dH", ESC, (int)y, (int)x);
}

void underline(uint8_t on) {
    if (on) {
        printf("%c[4m", ESC);
    } else {
        printf("%c[24m", ESC);
    }
}

void blink(uint8_t on) {
    if (on) {
        printf("%c[5m", ESC);
    } else {
        printf("%c[25m", ESC);
    }
}

void inverse(uint8_t on) {
    if (on) {
        printf("%c[7m", ESC);
    } else {
        printf("%c[27m", ESC);
    }
}

