/*
 * ansi.h
 *
 *  Created on: 14. jan. 2026
 *      Author: fueke
 */

#ifndef ANSI_H_
#define ANSI_H_

#include <stdint.h>
#include <stdio.h>

extern int counter;

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);

void clrscr();
void clreol();
void gotoxy(uint8_t x, uint8_t y);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);

void window(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, char* text);


#endif /* ANSI_H_ */
