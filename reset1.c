/////* Toggle LEDs on EduPad with TI Tiva LaunchPad
//// * 
//// * On EduPad board, PB3-PB0 are connected to the four LEDs.
//// * Default clock 50 MHz is used.
//// *
//// * Built and tested with Keil MDK-ARM v5.24a and TM4C_DFP v1.1.0
//// */

////#include "TM4C123GH6PM.h"

////void delayMs1(int n);

////int main1(void) {
////    volatile unsigned char readback;

////    // enable PORTB 3-0 as output
////    SYSCTL->RCGCGPIO |= 0x02;       // enable clock to GPIOB
////    readback = SYSCTL->RCGCGPIO;    // make sure the colock is enabled
////    GPIOB->DIR |= 0x0F;             // set PORTB 3-0 as output pins
////    GPIOB->DEN |= 0x0F;             // set PORTB 3-0 as digital pins

////    for (;;) {
////        GPIOB->DATA = 0x05;         // turn on PB2, 0
////        delayMs1(500);
////        GPIOB->DATA = 0x0A;         // turn on PB3, 1
////        delayMs1(500);
////    }
////}

/////* delay n milliseconds (50 MHz CPU clock) */
////void delayMs1(int n) {
////    int i, j;
////    for(i = 0 ; i< n; i++)
////        for(j = 0; j < 6265; j++)
////            {}  /* do nothing for 1 ms */
////}



//   //------------------------------------
//   