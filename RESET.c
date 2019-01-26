/* Toggle LEDs on EduPad with TI Tiva LaunchPad
 * 
 * On EduPad board, PB3-PB0 are connected to the four LEDs.
 * Default clock 50 MHz is used.
 *
 * Built and tested with Keil MDK-ARM v5.24a and TM4C_DFP v1.1.0
 */

#include "TM4C123GH6PM.h"

void delayMs(int n);

int main1(void) {
    volatile unsigned char readback;

    // enable PORTB 3-0 as output
    SYSCTL->RCGCGPIO |= 0x20;       // enable clock to GPIOB
    readback = SYSCTL->RCGCGPIO;    // make sure the colock is enabled
    GPIOF->DIR |= 0xFF;             // set PORTB 3-0 as output pins
    GPIOF->DEN |= 0xFF;             // set PORTB 3-0 as digital pins

    for (int i=0 ;i<3;i++) {
        GPIOF->DATA = 0xFF;         // turn on PB2, 0
        delayMs(1);
        GPIOF->DATA = 0xFF;         // turn on PB3, 1
        delayMs(1);
			UART_OutString("abduljAWAD");UART_OutString("abduljAWAD");UART_OutString("abduljAWAD");UART_OutString("abduljAWAD");
    }
}

/* delay n milliseconds (50 MHz CPU clock) */
