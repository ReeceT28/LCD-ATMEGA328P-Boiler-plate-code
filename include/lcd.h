
#ifndef LCD_H
#define LCD_H
#include <avr/io.h>
void lcd_initialise();       
void updateLCD(int xValue, int yValue, int potValue);  
void lcdcmdwrite(uint8_t data);  
void lcdwrite(const char *data_l);
void sendNibble(uint8_t data);  
char* intToString(int num);  

#endif
