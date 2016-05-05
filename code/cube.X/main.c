#include <xc.h>
#include <stdint.h>
#include "demo.h"

// CONFIG
#pragma config FOSC = HS    // Oscillator Selection bits
#pragma config WDTE = ON    // Watchdog Timer Enable bit
#pragma config PWRTE = OFF  // Power-up Timer Enable bit
#pragma config CP = OFF     // FLASH Program Memory Code Protection bits
#pragma config BOREN = OFF  // Brown-out Reset Enable bit
#pragma config LVP = OFF    // Low Voltage In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF    // Data EE Memory Code Protection
#pragma config WRT = OFF    // FLASH Program Memory Write Enable

// Timer initialization
inline void tm0init(void)
{
    // Regime
    OPTION_REGbits.T0CS = 0; // Internal generator
    OPTION_REGbits.PSA = 0; // On prescaler
    OPTION_REGbits.PS = 3; // 3 = Prescaler 1:16
    // On timer & interrupt
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
}

//----------------------------------------------------------------------
// Main function
void main(void)
{
    TRISA = TRISB = TRISC = TRISD = UINT8_MAX;
    TRISE = 0x07; // All pins - input
    while (!__timeout)
    { // Crit. fail! Watchdog reset
        TRISAbits.TRISA0 = TRISAbits.TRISA1 = 0;
        PORTAbits.RA0 = 1;
        PORTAbits.RA1 = 0;
        CLRWDT();
    }
    ADCON0bits.ADON = 0;
    ADCON1 = 0x06; // ADC off
    OPTION_REGbits.nRBPU = 1; // Disable upper resistors on port B
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;
    // Indicator of runing
    TRISAbits.TRISA0 = TRISAbits.TRISA1 = 0;
    PORTAbits.RA0 = 0;
    PORTAbits.RA1 = 0;
    demo_init();
    // On all interrupt
    INTCONbits.GIE = 1;
    CLRWDT();
    tm0init();
    while (1)
        demo_monitor();
}

//----------------------------------------------------------------------
// Interrupt
void interrupt intrpt (void)
{
    PORTAbits.RA1 = 1;
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) scan_irq();
    PORTAbits.RA1 = 0;
}
