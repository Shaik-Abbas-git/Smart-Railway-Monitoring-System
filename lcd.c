// lcd.c
#include "lcd.h"
#include "delay.h"

void LCD_WRT_4BIT(unsigned char byte)
{
    IOCLR0 = DATA_MASK_4BIT;
    IOSET0 = ((byte>>4)<<12);
    
    IOSET0 = EN_PIN;
    delay_ms(5);
    IOCLR0 = EN_PIN;
    
    IOCLR0 = DATA_MASK_4BIT;
    IOSET0 = ((byte & 0x0F)<<12);
    
    IOSET0 = EN_PIN;
    delay_ms(5);
    IOCLR0 = EN_PIN;
}

void LCD_CMD(unsigned char cmd)
{
    IOCLR0 = RS_PIN;
    LCD_WRT_4BIT(cmd);
}

void LCD_DATA(unsigned char data)
{
    IOSET0 = RS_PIN;
    LCD_WRT_4BIT(data);
}

void LCD_STR(char *str)
{
    while(*str != '\0')
    {
        LCD_DATA(*str);
        str++;
        delay_ms(20);
    }
}
void LCD_INIT(void)
{
    IODIR0 |= RS_PIN | EN_PIN | DATA_MASK_4BIT;
    
    // 4-bit forced reset sequence
    LCD_CMD(0x33);
    LCD_CMD(0x32);
    
   
    LCD_CMD(MODE_4BIT_2LINE);
    LCD_CMD(DSP_ON_CUR_OFF);
    LCD_CMD(CLEAR_LCD);
    LCD_CMD(SHIFT_CUR_RIGHT); 
}
