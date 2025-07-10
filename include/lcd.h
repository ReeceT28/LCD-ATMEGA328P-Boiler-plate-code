
#ifndef LCD_H
#define LCD_H
#include <avr/io.h>
void lcd_initialise();          // Fixed the typo here
void updateLCD(int xValue, int yValue, int potValue);  // Added parameters
void lcdcmdwrite(uint8_t data);  // Added parameter
void lcdwrite(const char *data_l); // Added parameter
void sendNibble(uint8_t data);  // Added parameter
char* intToString(int num);    // Added parameter

#endif
