/*
 * ansi.h
 *
 *  Created on: 13. jan. 2026
 *      Author: root
 */

#ifndef ANSI_H_
#define ANSI_H_

#include <stdint.h>

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor(void);

void clrscr(void);
void clreol(void);
void gotoxy(uint8_t x, uint8_t y);

void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);



#endif /* ANSI_H_ */
