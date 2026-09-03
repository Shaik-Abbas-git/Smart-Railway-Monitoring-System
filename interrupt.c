// interrupt.c
#include <LPC21xx.h>
#include "interrupt.h"

volatile u8 admin_menu_flag = 0;

// External interrupt service routine
void MENU_ISR(void) __irq
{
    admin_menu_flag = 1;

    // Clear the external interrupt and signal the VIC to exit the ISR
    EXTINT = (1 << 0);
    VICVectAddr = 0x00;
}


// Configure External Interrupt 0
void EINT0_INIT(void)
{
    // Configure P0.1 for EINT0
    PINSEL0 &= ~(3 << 2);
    PINSEL0 |= (3 << 2);

    // Configure falling-edge triggered interrupt
    EXTMODE = (1 << 0);
    EXTPOLAR &= ~(1 << 0);

    // Configure the Vectored Interrupt Controller
    VICIntSelect &= ~(1 << 14);
    VICVectAddr0 = (unsigned int)MENU_ISR;
    VICVectCntl0 = (1 << 5) | 14;
    VICIntEnable = (1 << 14);
}
