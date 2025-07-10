#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

const uint8_t DB4IO  = DDB1;
const uint8_t DB5IO  = DDB2;
const uint8_t DB6IO  = DDB3;
const uint8_t DB7IO  = DDB4; 
const uint8_t EIO    = DDB5;
const uint8_t RSIO   = DDB0 ;


char* intToString(int num) {
    static char bum[5];  // Static buffer to hold the string, including null terminator

    bum[4] = '\0'; // Null-terminate the string
    for (int i = 3; i >= 0; i--) {
        bum[i] = (num % 10) + '0'; // Convert last digit to character
        num /= 10; // Remove last digit from num
    }

    return bum;
}

void sendNibble(uint8_t data) {
    if(data & 0x01) PORTB|=(1<<DB4IO); else PORTB&=~(1<<DB4IO); //set D4
    if(data & 0x02) PORTB|=(1<<DB5IO); else PORTB&=~(1<<DB5IO); //set D5
    if(data & 0x04) PORTB|=(1<<DB6IO); else PORTB&=~(1<<DB6IO); //set D6
    if(data & 0x08) PORTB|=(1<<DB7IO); else PORTB&=~(1<<DB7IO); //set D7
    PORTB|=(1<<EIO); //pulse E on
    _delay_us(50); // Short delay to latch the data
    PORTB&=~(1<<EIO); //turn E off
    _delay_us(50); // Short delay after pulsing
  
  }

  void lcdcmdwrite(uint8_t data) {

    // Send the higher nibble
    sendNibble(data >> 4);
  
    // Send the lower nibble
    sendNibble(data);
  
    PORTB&=~(1<<RSIO); // turn RS low as we may not need it high if not sending characters
  
  }

  void lcdwrite(const char *data_l) {
    while(*data_l){
      PORTB|=(1<<RSIO); // tell lcd we are sending characters by turning RS HIGH
      lcdcmdwrite(*data_l);
      data_l++;
    }
  }


void lcd_initialise()
{
    _delay_ms(50); // Initial __delay_ms_ms for LCD power-up
  
    lcdcmdwrite(0x33); // Initialize for 4-bit mode (3 times as per spec)
    _delay_ms(5); // Delay after initialization command
    lcdcmdwrite(0x32); // Set to 4-bit mode
    _delay_ms(5); // Delay after setting to 4-bit mode
  
    lcdcmdwrite(0x28); // 2 lines, 5x7 matrix
    _delay_ms(2); // Delay after setting function
  
    lcdcmdwrite(0x0C); // Display on, cursor off
    _delay_ms(2); // Delay after display on command
  
    lcdcmdwrite(0x06); // Increment cursor
    _delay_ms(2); // Delay after entry mode set
  
    lcdcmdwrite(0x01); // Clear display
    _delay_ms(2); // Delay after clearing the display
}


void updateLCD(int xValue, int yValue, int potValue) 
{
    lcdcmdwrite(0x82); // Move to position after X:
    lcdwrite(intToString(xValue));
    lcdcmdwrite(0x89); // position after Y:
    lcdwrite(intToString(yValue));
    lcdcmdwrite(0xC4); //position after Pot:
    lcdwrite(intToString(potValue));
}
  
