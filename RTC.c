// RTC.c
#include <LPC21xx.h>
#include "RTC.h"
#include "lcd.h"
#include "keypad.h"
#include "delay.h"
#include "types.h"

const char* day_names[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};


void digi_2format(int value, char *str)
{
    str[0] = (value / 10) + '0';
    str[1] = (value % 10) + '0';
    str[2] = '\0';
}


void RTC_INIT(void)
{
    CCR = 0x00;

    PREINT = 356;
    PREFRAC = 25026;

    SEC = 00;
    MIN = 0;
    HOUR = 0;
    DOM = 0;
    DOW = 0;
    MONTH = 0;
    YEAR = 2026;

    CCR = 0x01;
}


void Display_state(void)
{
    char temp_str[3];

    LCD_CMD(GOTO_LINE1_POS0);

    digi_2format(HOUR, temp_str);
    LCD_STR(temp_str);
    LCD_DATA(':');

    digi_2format(MIN, temp_str);
    LCD_STR(temp_str);
    LCD_DATA(':');

    digi_2format(SEC, temp_str);
    LCD_STR(temp_str);

    LCD_STR("   ");
    LCD_STR((char*)day_names[DOW]);

    LCD_CMD(0xC2);

    digi_2format(DOM, temp_str);
    LCD_STR(temp_str);
    LCD_DATA('/');

    digi_2format(MONTH, temp_str);
    LCD_STR(temp_str);
    LCD_DATA('/');

    LCD_STR("20");
    digi_2format(YEAR % 100, temp_str);    // Display the last two digits of the year
    LCD_STR(temp_str);
}


int Get_Numeric_Input(char *prompt, int min_val, int max_val)
{
    int val = 0;
    char key;

    LCD_CMD(0x01);
    LCD_STR(prompt);

    while (1)
    {
        LCD_CMD(0xC0);
        LCD_DATA((val / 10) + '0');
        LCD_DATA((val % 10) + '0');
        LCD_STR("  ");

        key = Read_Keypad();

        if (key != '\0')
        {
            if (key >= '0' && key <= '9')
            {
                val = (val * 10) + (key - '0');

                if (val > 99)
                    val = val % 100;
            }
            else if (key == 'C')
            {
                val = val / 10;
            }
            else if (key == '=')
            {
                if (val >= min_val && val < max_val)
                {
                    return val;
                }

                LCD_CMD(0x01);
                LCD_STR("INVALID ENTRY");
                delay_ms(1000);

                val = 0;

                LCD_CMD(0x01);
                LCD_STR(prompt);
            }
        }
    }
}


void Set_RTC_Date_Time(void)
{
    char key;
    int temp;
    u8 exit_rtc = 0;
    u8 menu_level = 0;
    u8 draw_menu = 1;

    while (exit_rtc == 0)
    {
        // Display the current RTC menu only when required
        if (draw_menu == 1)
        {
            LCD_CMD(0x01);

            if (menu_level == 0)
            {
                LCD_STR("1:Date 2:Time");
                LCD_CMD(0xC0);
                LCD_STR("C:Back to Admin");
            }
            else if (menu_level == 1)
            {
                LCD_STR("1:DD 2:MM 3:YY");
                LCD_CMD(0xC0);
                LCD_STR("4:Day  C:Back");
            }
            else if (menu_level == 2)
            {
                LCD_STR("1:HH 2:Min 3:Sec");
                LCD_CMD(0xC0);
                LCD_STR("C:Back");
            }

            draw_menu = 0;
        }

        key = Read_Keypad();

        if (key != '\0')
        {
            // D exits the RTC settings directly
            if (key == 'D')
            {
                exit_rtc = 1;
                continue;
            }

            if (menu_level == 0)
            {
                if (key == '1')
                {
                    menu_level = 1;
                    draw_menu = 1;
                }
                else if (key == '2')
                {
                    menu_level = 2;
                    draw_menu = 1;
                }
                else if (key == 'C')
                {
                    exit_rtc = 1;
                }
            }
            else if (menu_level == 1)
            {
                if (key == '1')
                {
                    temp = Get_Numeric_Input("Set Date(1-31):", 1, 32);

                    CCR = 0x00;
                    DOM = temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == '2')
                {
                    temp = Get_Numeric_Input("Set Mnth(1-12):", 1, 13);

                    CCR = 0x00;
                    MONTH = temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == '3')
                {
                    temp = Get_Numeric_Input("Set Year(0-99):", 0, 100);

                    CCR = 0x00;
                    YEAR = 2000 + temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == '4')
                {
                    temp = Get_Numeric_Input("Day(0=Sun,6=Sat):", 0, 7);

                    CCR = 0x00;
                    DOW = temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == 'C')
                {
                    menu_level = 0;
                    draw_menu = 1;
                }
            }
            else if (menu_level == 2)
            {
                if (key == '1')
                {
                    temp = Get_Numeric_Input("Set Hour(0-23):", 0, 24);

                    CCR = 0x00;
                    HOUR = temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == '2')
                {
                    temp = Get_Numeric_Input("Set Mins(0-59):", 0, 60);

                    CCR = 0x00;
                    MIN = temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == '3')
                {
                    temp = Get_Numeric_Input("Set Secs(0-59):", 0, 60);

                    CCR = 0x00;
                    SEC = temp;
                    CCR = 0x01;

                    draw_menu = 1;
                }
                else if (key == 'C')
                {
                    menu_level = 0;
                    draw_menu = 1;
                }
            }
        }
    }
}
