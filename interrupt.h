//interrupt.h
#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "types.h"

extern volatile u8 admin_menu_flag; 

void EINT0_INIT(void);
void MENU_ISR(void) __irq;

#endif
