///////* UART1 echo
////// *
////// * Pin header J34 is connected to UART1.
////// * Pin 2 - Tx (PB1)
////// * Pin 3 - Rx (PB0)
////// * The UART1 is configure for 9600 Baud 8-N-1.
////// * Connect a USB to 3.3V serial converter to a PC and launch a
////// * terminal emulator on the PC. The keyboard input will be sent
////// * by the terminal emulator to USB-serial converter. Connect the
////// * Tx pin of the converter to the Rx (pin 3 of J34). This program
////// * echoes back the characters to the Tx (pin 2 of J34). Connect Tx
////// * of J34 to Rx of the USB-Serial converter and the character will
////// * appear on the terminal emulator window.
////// *
////// * Built and tested with Keil MDK-ARM v5.24a and TM4C_DFP v1.1.0
////// */

//////#include <stdint.h>
//////#include "TM4C123.h"

//////void UART1Tx(char c);
//////unsigned char UART1Rx(void);
//////void delayMs(int n);

//////int main(void) {
//////    char c;
//////    
//////    SYSCTL->RCGCUART |= 2;  /* provide clock to UART1 */
//////    SYSCTL->RCGCGPIO |= 2;  /* enable clock to PORTB */
//////    
//////    /* UART1 initialization */
//////    UART1->CTL = 0;         /* disable UART1 */
//////    UART1->IBRD = 325;      /* 50MHz/16=3.125MHz, 3.125MHz/325=9600 baud rate */
//////    UART1->FBRD = 33;       /* fraction part, see Example 4-4 */
//////    UART1->CC = 0;          /* use system clock */
//////    UART1->LCRH = 0x60;     /* 8-bit, no parity, 1-stop bit, no FIFO */
//////    UART1->CTL = 0x301;     /* enable UART1, TXE, RXE */

//////    /* UART1 TX0 and RX0 use PB1 and PB0. Set them up. */
//////    GPIOB->DEN = 0x03;      /* Make PB0 and PB1 as digital */
//////    GPIOB->AFSEL = 0x03;    /* Use PB0,PB1 alternate function */
//////    GPIOB->PCTL = 0x11;     /* configure PB0 and PB1 for UART */
//////    
//////    delayMs(1);             /* wait for output line to stabilize */

//////    UART1Tx('>');
//////    
//////    for(;;) {
//////        c = UART1Rx();
//////        if (c == '\r')
//////            UART1Tx('\n'); 
//////        UART1Tx(c); 
//////    }
//////}

///////* UART1 Transmit
////// * This function waits until the transmit buffer is available then
////// * write the character in the transmit buffer.  It does not wait
////// * for transmission to complete.
////// */
//////void UART1Tx(char c) {
//////    while((UART1->FR & 0x20) != 0); /* wait until Tx buffer not full */
//////    UART1->DR = c;                  /* before giving it another byte */
//////}


//////unsigned char UART1Rx(void){
//////    char c;
//////    while((UART1->FR & 0x10) != 0); // wait until the buffer is not empty
//////    c = UART1->DR;                  // read the received data
//////    return c;                       // and return it
//////}


///////* delay n milliseconds (50 MHz CPU clock) */
//////void delayMs(int n) {
//////    int i, j;
//////    for(i = 0 ; i< n; i++)
//////        for(j = 0; j < 6265; j++)
//////            {}  /* do nothing for 1 ms */
//////}