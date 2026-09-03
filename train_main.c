// train_main.c
#include <LPC21xx.h>
#include "types.h"
#include "RTC.h"
#include "railway.h"
#include "lcd.h"
#include "delay.h"
#include "interrupt.h"
#include "admin.h"
#include "keypad.h"
#include "train_dprint.h"
#include "indicator.h"


int main()
{
    u8 active_list[TOTAL_TRAINS];
    u8 total_active = 0;
    u8 current_slot = 0;
    u8 i;
    u8 train_to_show;
    u8 is_done;

    u8 current_idle_state = 0;
    s8 last_idle_state = -1;

    u32 live_mins;
    u32 updated_arr_mins;
    u32 updated_dep_mins;

    s32 start_diff;
    s32 end_diff;


    // Initialize hardware
    delay_ms(100);
    LCD_INIT();
    RTC_INIT();
    EINT0_INIT();
    KEYPAD_INIT();

    Set_RTC_Date_Time();

    // Configure GPIO pins used by LEDs and buzzer
    PINSEL0 &= ~(0x0000FF00);
    IO0DIR |= ALL_INDICATORS;
    IO0CLR = ALL_INDICATORS;


    while(1)
    {
        // Normal monitoring mode
        if(admin_menu_flag == 0)
        {
            total_active = 0;

            for(i = 0; i < TOTAL_TRAINS; i++)
            {
                live_mins = Time_To_Minutes(HOUR, MIN);

                updated_arr_mins = Time_To_Minutes(
                    TrainDB[i].updatedArrivalHour,
                    TrainDB[i].updatedArrivalMinute
                );

                updated_dep_mins = Time_To_Minutes(
                    TrainDB[i].updatedDepartureHour,
                    TrainDB[i].updatedDepartureMinute
                );

                start_diff = updated_arr_mins - live_mins;
                end_diff = updated_dep_mins - live_mins;

                // Handle time comparison across midnight
                if(start_diff < -720)
                    start_diff += 1440;

                if(end_diff < -720)
                    end_diff += 1440;

                // Check whether the train is approaching and has not departed
                if(start_diff <= 5 && end_diff >= 0)
                {
                    active_list[total_active] = i;
                    total_active++;
                }
            }


            // Display approaching trains
            if(total_active > 0)
            {
                last_idle_state = -1;

                if(current_slot >= total_active)
                    current_slot = 0;

                train_to_show = active_list[current_slot];

                Update_Indicators(train_to_show, 1);

                is_done = Display_Train_Approaching(
                    &TrainDB[train_to_show]
                );

                // Move to the next active train after the animation completes
                if(is_done == 1 && total_active > 1)
                    current_slot++;
            }


            // Display idle station information
            else
            {
                u8 current_sec = SEC % 18;

                if(current_sec < 6)
                    current_idle_state = 0;
                else if(current_sec < 8)
                    current_idle_state = 1;
                else if(current_sec < 10)
                    current_idle_state = 2;
                else if(current_sec < 12)
                    current_idle_state = 3;
                else if(current_sec < 14)
                    current_idle_state = 4;
                else if(current_sec < 16)
                    current_idle_state = 5;
                else
                    current_idle_state = 6;


                // Redraw the LCD only when the display state changes
                if(current_idle_state != last_idle_state)
                {
                    last_idle_state = current_idle_state;
                    LCD_CMD(0x01);

                    if(current_idle_state == 1)
                    {
                        Display_Train_Summary(0, 0);
                        Update_Indicators(0, 0);
                    }

                    if(current_idle_state == 2)
                    {
                        Display_Train_Summary(0, 1);
                        Update_Indicators(0, 0);
                    }

                    if(current_idle_state == 3)
                    {
                        Display_Train_Summary(1, 0);
                        Update_Indicators(1, 0);
                    }

                    if(current_idle_state == 4)
                    {
                        Display_Train_Summary(1, 1);
                        Update_Indicators(1, 0);
                    }

                    if(current_idle_state == 5)
                    {
                        Display_Train_Summary(2, 0);
                        Update_Indicators(2, 0);
                    }

                    if(current_idle_state == 6)
                    {
                        Display_Train_Summary(2, 1);
                        Update_Indicators(2, 0);
                    }
                }


                if(current_idle_state == 0)
                {
                    IO0CLR = ALL_INDICATORS;
                    Display_state();
                }
            }

            delay_ms(10);
        }


        // Admin mode triggered by external interrupt
        if(admin_menu_flag == 1)
        {
            Run_Admin_Menu();
        }
    }
}
