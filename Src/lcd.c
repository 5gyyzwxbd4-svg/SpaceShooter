/*
 * lcd.c
 *
 *  Created on: 14. jan. 2026
 *      Author: fueke
 */


#include "lcd.h"
#include "charset.h"
#include "string.h"
#include "timer.h"

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

void lcd_write_string_px(const char* text, uint8_t x, uint8_t y, uint8_t* buffer)
{
    for (uint8_t i = 0; text[i] != '\0'; i++)
    {
        lcd_write_char_px(text[i], x + i*6, y, buffer);
    }
}

void lcd_write_char_px(char c, uint8_t x, uint8_t y, uint8_t* buffer)
{
    if (c < 0x20 || c > 0x7E) return;

    uint8_t index = c - 0x20;

    for (uint8_t col = 0; col < 5; col++)
    {
        uint8_t col_data = character_data[index][col];

        for (uint8_t row = 0; row < 7; row++)
        {
            if ((col_data >> row) & 0x01)
            {
                uint8_t px = x + col;
                uint8_t py = y + row;

                uint8_t page = py / 8;
                uint8_t bit  = py % 8;

                if (px < 128 && page < 8)
                {
                    buffer[page * 128 + px] |= (1 << bit);
                }
            }
        }
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

// Tegner life antal hjerter, starter ved x_start
void lcd_draw_lives(uint8_t x_start, uint8_t y, uint8_t* buffer, uint8_t life)
{
    if (life == 0) return; // intet hjerte

    const uint8_t heart_width = 7; // 5 px + 2 px spacing

    // Midten af "LIVES:" som reference
    uint8_t mid_x = 12 + 15; // "LIVES:" starter x=12, LIVES: = 6 tegn
    // Her antager vi label bredde ca 18 px (6 tegn * 3 px), justér hvis du vil mere præcist

    // Beregn start_x, så hjerterne centreres under label
    int16_t start_x = mid_x - ((life * heart_width) / 2);

    // Tegn livene
    for (uint8_t i = 0; i < life; i++)
    {
        lcd_draw_tiny_heart(start_x + i*heart_width, y, buffer);
    }
}

/* Tegn tre hjerter ved siden af */
void lcd_draw_tre_hearts(uint8_t x, uint8_t y, uint8_t* buffer)
{
    lcd_draw_tiny_heart(x + 0, y, buffer);
    lcd_draw_tiny_heart(x + 10, y, buffer);
    lcd_draw_tiny_heart(x + 20, y, buffer);
}

void lcd_draw_time_label(uint8_t x, uint8_t line, uint8_t* buffer)
{
    lcd_write_string('T', x + 0, line, buffer);
    lcd_write_string('I', x + 6, line, buffer);
    lcd_write_string('M', x + 12, line, buffer);
    lcd_write_string('E', x + 18, line, buffer);
    lcd_write_string(':', x + 24, line, buffer);
}


/*void update_score(timer15_init())
{
	//skal opdatere fra player()
	//skal +1 for hvert 2. sekund
	// +100 for hver gang vi rammer 1 minut
}*/

uint32_t calculate_score(void)
{
    // Beregn total sekunder fra timer
    uint16_t total_seconds = tick_10ms / 100;

    // +1 point pr 2. sekund
    uint32_t points_from_seconds = total_seconds / 2;

    // +100 point pr minut
    uint32_t points_from_minutes = (total_seconds / 60) * 100;

    return points_from_seconds + points_from_minutes;
}

void lcd_draw_score_value(uint8_t x, uint8_t y, uint8_t* buffer)
{
    uint16_t total_seconds = tick_10ms / 100; //stiger 1 pr ms fra TIM15 (1sek = 100ticks)
    uint32_t score = (total_seconds / 2) + ((total_seconds / 60) * 100); // 1point pr 2 sek + 100point pr 1min

    char score_str[12]; 					//danner en string for score
    sprintf(score_str, "%lu", score);		//"%lu" for unsigned long integers (long unsigned)

    // For at den starter i højre side
        uint8_t char_width = 5;
        uint8_t spacing = 1;
        uint8_t total_width = strlen(score_str) * (char_width + spacing);
        uint8_t start_x = 126 - total_width + 1; // sidste karakter på x=126

    for (uint8_t i = 0; score_str[i] != '\0'; i++)
    {
    	lcd_write_string_px(&score_str[i], start_x + i*(char_width + spacing), y, buffer); 	// 1 tegn ad gangen.
        	//pointer til hvert enkelte tegn i score, fordi funktionen forventer char* og ikke string
        	// "x + i*6" (forskyder før næste tegn) hver tegn er 5 pixels bred + 1 pixel spacing = 6
    }
}
