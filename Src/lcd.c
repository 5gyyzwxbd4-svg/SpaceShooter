/*
 * lcd.c
 *
 *  Created on: 14. jan. 2026
 *      Author: fueke
 */


#include "lcd.h"
#include "charset.h"
#include "string.h"

extern const uint8_t font5x7[][5];
//extern void lcd_write_string(char c,uint16_t slice, int line,uint8_t* buffer);

/* Opdater LCD */
void update_lcd(uint8_t* buffer)
{
    lcd_push_buffer(buffer);
}

/* Tegn et enkelt tegn fra character_data */
void lcd_write_string(char c,uint16_t slice, int line,uint8_t* buffer){

	int col;
	uint8_t index;
	if(c<0x20 || c>0x7E){
		return;
	}
	index = c - 0x20;

	for (col = 0; col<5;col++){
		buffer[line*128+slice+col] = character_data[index][col];
	}
}

/* Tegn LIV: nederst */
void lcd_draw_lives_label(uint8_t x, uint8_t line, uint8_t* buffer)
{
    lcd_write_string('L', x + 0, line, buffer);
    lcd_write_string('I', x + 6, line, buffer);
    lcd_write_string('V', x + 12, line, buffer);
    lcd_write_string('E', x + 18, line, buffer);
    lcd_write_string('S', x + 24, line, buffer);
    lcd_write_string(':', x + 30, line, buffer);
}


void lcd_draw_tiny_heart(uint8_t x, uint8_t y, uint8_t* buffer)
{
    // Tiny heart 5x5 pixels (lokal const)
    const uint8_t tiny_heart[5] = {
        0b01010,  // row 0
        0b11111,  // row 1
        0b11111,  // row 2
        0b01110,  // row 3
        0b00100   // row 4
    };

    for (uint8_t row = 0; row < 5; row++)
    {
        uint8_t page = (y + row) / 8;     // hvilken page
        uint8_t bit  = (y + row) % 8;     // hvilken bit i byte

        for (uint8_t col = 0; col < 5; col++)
        {
            if ((tiny_heart[row] >> (4 - col)) & 0x01)
            {
                buffer[page*128 + x + col] |= (1 << bit);
            }
        }
    }
}

/* Tegn tre hjerter ved siden af */
void lcd_draw_tre_hearts(uint8_t x, uint8_t y, uint8_t* buffer)
{
    lcd_draw_tiny_heart(x + 0, y, buffer);
    lcd_draw_tiny_heart(x + 10, y, buffer);
    lcd_draw_tiny_heart(x + 20, y, buffer);
}


