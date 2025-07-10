#include "lcd.h"
#include <util/delay.h>

// Setup function to initialize LCD
void setup() 
{
  uint8_t DB4IO  = DDB1;
  uint8_t DB5IO  = DDB2;
  uint8_t DB6IO  = DDB3;
  uint8_t DB7IO  = DDB4; 
  uint8_t EIO    = DDB5;
  uint8_t RSIO   = DDB0;
  DDRB|=(1<<DB7IO)|(1<<DB6IO)|(1<<RSIO)|(1<<EIO)|(1<<DB5IO)|(1<<DB4IO); 
  _delay_ms(100);
  lcd_initialise();  // Initialize the LCD
  _delay_ms(100);
  lcdwrite("Everyone is "); 
  lcdcmdwrite(0xC0);  // Move to second line of the LCD
  lcdwrite("always connected "); 
}

// Empty loop function (not needed for this example)
void loop() 
{

}

// Main function
int main(void)
{
    setup();  // Initialize and display the message

    while(1)
    {
        loop();  // Enter the loop - empty right now but can add code here
    }

    return 0;  // End of main (not necessary but included for clarity)
}
