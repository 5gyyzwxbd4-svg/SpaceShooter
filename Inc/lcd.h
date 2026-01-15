/*
 * lcd.h
 *
 *  Created on: 14. jan. 2026
 *      Author: fueke
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f30x.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_gpio.h"
#include "charset.h"
#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h"

//extern const uint8_t font5x7[][5];  // behold denne som før

// LCD funktioner

void lcd_init(void);
void lcd_push_buffer(uint8_t* buffer);
void update_lcd(uint8_t* buffer);

// Tegn tekst
void lcd_write_string(char c, uint16_t x, int y, uint8_t* buffer);
void lcd_draw_lives_label(uint8_t x, uint8_t y, uint8_t* buffer);

// Tegn hjerter
void lcd_draw_tiny_heart(uint8_t x, uint8_t y, uint8_t* buffer);
void lcd_draw_tre_hearts(uint8_t x, uint8_t y, uint8_t* buffer);

#endif /* LCD_H_ */
