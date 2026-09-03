//lcd.h
#ifndef LCD_H
#define LCD_H

#include <LPC21xx.h>
#include "delay.h"

//Pin Definitions
#define RS_PIN (1<<10)
#define EN_PIN (1<<11)
#define DATA_MASK_4BIT (0x0F<<12)

// LCD Commands
#define CLEAR_LCD            0x01
#define RET_CUR_HOME         0x02
#define SHIFT_CUR_RIGHT      0x06
#define SHIFT_CUR_LEFT       0x07
#define DSP_OFF              0x08
#define DSP_ON_CUR_OFF       0x0C
#define DSP_ON_CUR_ON        0x0E
#define DSP_ON_CUR_BLK       0x0F
#define SHIFT_DSP_LEFT       0x10
#define SHIFT_DSP_RIGHT      0x14
#define MODE_8BIT_1LINE      0x30
#define MODE_4BIT_1LINE      0x20
#define MODE_8BIT_2LINE      0x38
#define MODE_4BIT_2LINE      0x28
#define GOTO_LINE1_POS0      0x80
#define GOTO_LINE2_POS0      0xC0
#define GOTO_LINE3_POS0      0x94
#define GOTO_LINE4_POS0      0xD4
#define GOTO_CGRAM_START     0x40

//Function Prototypes
void LCD_WRT_4BIT(unsigned char byte);
void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_STR(char *str);
void LCD_INIT(void);

#endif
