
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 6000000


unsigned char count;
void main()
{
    TRISC=0x00; //setting TRISC as output
    TRISD=0x00; //setting TRISD as output
    PORTC=0x00; //setting PORTC as output
    PORTD=0x00; //setting PORTD as output
    INTCON|=0xC0; //Enbling GIE AND PEIE 
    PIE1|=0x01; //Enbaling timer1
    T1CON|=0x01; //Enbaling timer1
    TMR1=5475; //preloading value
    
    while(1)
    {
        PORTD=0x00;  //Led off
        __delay_ms(500);
        PORTD=0xFF;  //Led on
        __delay_ms(500);
    }
}
void __interrupt() ISR()
{
  if(PIR1 & 0x01)  // Check if Timer1 overflow flag is set
    {
        count++;  // Increment count variable
        if(count==25)  // Check if count reaches 25
        {
        PORTC=~PORTC; // Toggle the LEDs on PORTC
        count=0;  // Reset count to 0
        }
        TMR1=5475;  // Reload Timer1 with initial value after one overflow
        PIR1 &=0xFE;  // Clear Timer1 overflow flag
        
    }
    }