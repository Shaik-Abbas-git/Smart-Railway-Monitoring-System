//admin.c
#include <LPC21xx.h>
#include "admin.h"
#include "lcd.h"
#include "keypad.h"
#include "interrupt.h"
#include "delay.h"
#include "railway.h"
#include "RTC.h"
#include "train_dprint.h"


// Print an integer on the LCD without using sprintf()
void LCD_PRINT_INT(u32 num)
{
    char buf[10];
    s8 i = 0;

    if (num == 0)
    {
        LCD_DATA('0');
        return;
    }

    // Extract digits in reverse order
    while (num > 0)
    {
        buf[i] = (num % 10) + '0';
        num = num / 10;
        i++;
    }

    // Print digits in the correct order
    while (i > 0)
    {
        i--;
        LCD_DATA(buf[i]);
    }
}


// Check whether the proposed train timings overlap another train
s8 Check_Platform_Collision(s8 test_train_id, u32 p_delay, u8 p_plt,
                            u32 p_arr_hhmm, u32 p_dep_hhmm)
{
    u8 i;
    u32 test_arr, test_dep;
    u32 check_arr, check_dep;

    u32 arr_h = p_arr_hhmm / 100;
    u32 arr_m = p_arr_hhmm % 100;
    u32 dep_h = p_dep_hhmm / 100;
    u32 dep_m = p_dep_hhmm % 100;

    test_arr = Time_To_Minutes(arr_h, arr_m) + p_delay;
    test_dep = Time_To_Minutes(dep_h, dep_m) + p_delay;

    if (test_dep < test_arr)
        test_dep += 1440;

    for (i = 0; i < TOTAL_TRAINS; i++)
    {
        if (i == test_train_id)
            continue;

        if (TrainDB[i].platform == 0 || TrainDB[i].platform > 9)
            continue;

        if (TrainDB[i].platform == p_plt)
        {
            check_arr = Time_To_Minutes(
                TrainDB[i].arrivalHour,
                TrainDB[i].arrivalMinute
            ) + TrainDB[i].delayMinutes;

            check_dep = Time_To_Minutes(
                TrainDB[i].departureHour,
                TrainDB[i].departureMinute
            ) + TrainDB[i].delayMinutes;

            if (check_dep < check_arr)
                check_dep += 1440;

            if ((test_arr < check_dep) && (test_dep > check_arr))
            {
                return i;
            }
        }
    }

    return -1;
}


// Admin menu state machine
void Run_Admin_Menu(void)
{
    u8 exit_menu = 0;
    s8 step = -2;
    s8 selected_train = -1;
    u8 edit_target = 0;
    u32 total_input = 0;

    char pass_buff[5] = {0};
    u8 pass_idx = 0;
    char key;

    u8 is_valid;
    u32 p_delay, p_plt, p_arr, p_dep;
    s8 blocking_train;
    u32 new_arr, new_dep;
    u32 h, m;

    IO0CLR = BUZZER;

    // Display the PIN screen before entering the menu loop
    LCD_CMD(0x01);
    LCD_STR("ENTER ADMIN PIN:");
    LCD_CMD(0xC0);

    while (exit_menu == 0)
    {
        key = Read_Keypad();

        if (key != '\0')
        {
            // D exits the admin menu directly
            if (key == 'D')
            {
                exit_menu = 1;
                continue;
            }

            // PIN authentication
            if (step == -2)
            {
                if (key == 'C')
                {
                    exit_menu = 1;
                }
                else if (key == '=')
                {
                    pass_buff[pass_idx] = '\0';

                    if (pass_buff[0] == '1' &&
                        pass_buff[1] == '2' &&
                        pass_buff[2] == '3' &&
                        pass_buff[3] == '4' &&
                        pass_idx == 4)
                    {
                        LCD_CMD(0x01);
                        LCD_STR("1:Edit RTC Time");
                        LCD_CMD(0xC0);
                        LCD_STR("2:Edit Trains");
                        step = 11;
                    }
                    else
                    {
                        LCD_CMD(0x01);
                        LCD_STR("ACCESS DENIED");
                        delay_ms(1000);
                        exit_menu = 1;
                    }
                }
                else if (key >= '0' && key <= '9')
                {
                    if (pass_idx < 4)
                    {
                        pass_buff[pass_idx] = key;
                        pass_idx++;
                        LCD_DATA('*');
                    }
                }
            }

            // Master menu
            else if (step == 11)
            {
                if (key == '1')
                {
                    Set_RTC_Date_Time();

                    LCD_CMD(0x01);
                    LCD_STR("1:Edit RTC Time");
                    LCD_CMD(0xC0);
                    LCD_STR("2:Edit Trains");
                    step = 11;
                }
                else if (key == '2')
                {
                    LCD_CMD(0x01);
                    LCD_STR("1KRN 2SHB 3KACH");
                    LCD_CMD(0xC0);
                    LCD_STR("Select(1-3):");
                    step = 1;
                }
                else if (key == 'C')
                {
                    exit_menu = 1;
                }
            }

            // Train selection
            else if (step == 1)
            {
                if (key == 'C')
                {
                    LCD_CMD(0x01);
                    LCD_STR("1:Edit RTC Time");
                    LCD_CMD(0xC0);
                    LCD_STR("2:Edit Trains");
                    step = 11;
                }
                else if (key >= '1' && key <= '3')
                {
                    selected_train = (key - '0') - 1;

                    LCD_CMD(0x01);
                    LCD_STR("Selected:");
                    LCD_CMD(0xC0);
                    LCD_STR(TrainDB[selected_train].trainName);
                    delay_ms(1500);

                    LCD_CMD(0x01);
                    LCD_STR("1:Dly 2:Plt");
                    LCD_CMD(0xC0);
                    LCD_STR("3:Arr 4:Dep");
                    step = 2;
                }
                else
                {
                    LCD_CMD(0xC0);
                    LCD_STR("INVALID! Try 1-3");
                    delay_ms(1000);
                    LCD_CMD(0xC0);
                    LCD_STR("Select(1-3):    ");
                }
            }

            // Select the train data to edit
            else if (step == 2)
            {
                if (key == 'C')
                {
                    LCD_CMD(0x01);
                    LCD_STR("1KRN 2SHB 3KACH");
                    LCD_CMD(0xC0);
                    LCD_STR("Select(1-3):");
                    step = 1;
                }
                else if (key >= '1' && key <= '4')
                {
                    edit_target = key - '0';

                    LCD_CMD(0x01);

                    if (edit_target == 1)
                        LCD_STR("Enter Delay(m):");

                    if (edit_target == 2)
                        LCD_STR("Enter Platform:");

                    if (edit_target == 3)
                        LCD_STR("Arr Time(HHMM):");

                    if (edit_target == 4)
                        LCD_STR("Dep Time(HHMM):");

                    LCD_CMD(0xC0);
                    total_input = 0;
                    step = 3;
                }
            }

            // Numeric data entry
            else if (step == 3)
            {
                if (key == 'C')
                {
                    LCD_CMD(0x01);
                    LCD_STR("1:Dly 2:Plt");
                    LCD_CMD(0xC0);
                    LCD_STR("3:Arr 4:Dep");
                    step = 2;
                }
                else if (key == '-')
                {
                    total_input = total_input / 10;

                    LCD_CMD(0xC0);
                    LCD_STR("                ");
                    LCD_CMD(0xC0);

                    if (total_input > 0)
                        LCD_PRINT_INT(total_input);
                }
                else if (key == '=')
                {
                    step = 4;
                }
                else if (key >= '0' && key <= '9')
                {
                    if (total_input < 1000)
                    {
                        total_input = (total_input * 10) + (key - '0');

                        LCD_CMD(0xC0);
                        LCD_STR("                ");
                        LCD_CMD(0xC0);
                        LCD_PRINT_INT(total_input);
                    }
                }
            }

            // Validate the entered data
            if (step == 4)
            {
                is_valid = 1;

                if (edit_target == 2 &&
                    (total_input == 0 || total_input > 9))
                    is_valid = 0;

                if (edit_target == 1 && total_input > 1440)
                    is_valid = 0;

                if (edit_target == 3 || edit_target == 4)
                {
                    h = total_input / 100;
                    m = total_input % 100;

                    if (h > 23 || m > 59)
                        is_valid = 0;
                }

                if (is_valid == 1)
                {
                    p_delay = TrainDB[selected_train].delayMinutes;
                    p_plt = TrainDB[selected_train].platform;

                    p_arr = (TrainDB[selected_train].arrivalHour * 100) +
                            TrainDB[selected_train].arrivalMinute;

                    p_dep = (TrainDB[selected_train].departureHour * 100) +
                            TrainDB[selected_train].departureMinute;

                    if (edit_target == 1)
                        p_delay = total_input;

                    if (edit_target == 2)
                        p_plt = total_input;

                    if (edit_target == 3)
                        p_arr = total_input;

                    if (edit_target == 4)
                        p_dep = total_input;

                    blocking_train = Check_Platform_Collision(
                        selected_train,
                        p_delay,
                        p_plt,
                        p_arr,
                        p_dep
                    );

                    if (blocking_train != -1)
                    {
                        LCD_CMD(0x01);
                        LCD_STR("COLLISION ERROR");
                        LCD_CMD(0xC0);
                        LCD_STR("Blocked by:");
                        LCD_PRINT_INT(TrainDB[blocking_train].trainNumber);

                        IO0SET = BUZZER;
                        delay_ms(2000);
                        IO0CLR = BUZZER;

                        is_valid = 0;
                    }
                }

                if (is_valid == 0)
                {
                    LCD_CMD(0x01);
                    LCD_STR("INVALID INPUT");
                    delay_ms(1500);

                    LCD_CMD(0x01);

                    if (edit_target == 1)
                        LCD_STR("Enter Delay(m):");

                    if (edit_target == 2)
                        LCD_STR("Enter Platform:");

                    if (edit_target == 3)
                        LCD_STR("Arr Time(HHMM):");

                    if (edit_target == 4)
                        LCD_STR("Dep Time(HHMM):");

                    LCD_CMD(0xC0);

                    total_input = 0;
                    step = 3;
                }
                else
                {
                    LCD_CMD(0x01);
                    LCD_STR("Confirm Change?");
                    LCD_CMD(0xC0);
                    LCD_STR("*=Save  C=Cancel");
                    step = 5;
                }
            }

            // Save the validated changes
            else if (step == 5)
            {
                if (key == 'C')
                {
                    LCD_CMD(0x01);
                    LCD_STR("1:Dly 2:Plt");
                    LCD_CMD(0xC0);
                    LCD_STR("3:Arr 4:Dep");
                    step = 2;
                }
                else if (key == '*')
                {
                    if (edit_target == 1)
                    {
                        TrainDB[selected_train].delayMinutes = total_input;
                        TrainDB[selected_train].status = 1;
                    }
                    else if (edit_target == 2)
                    {
                        TrainDB[selected_train].platform = total_input;
                    }
                    else if (edit_target == 3)
                    {
                        TrainDB[selected_train].arrivalHour = total_input / 100;
                        TrainDB[selected_train].arrivalMinute = total_input % 100;
                    }
                    else if (edit_target == 4)
                    {
                        TrainDB[selected_train].departureHour = total_input / 100;
                        TrainDB[selected_train].departureMinute = total_input % 100;
                    }

                    new_arr = Time_To_Minutes(
                        TrainDB[selected_train].arrivalHour,
                        TrainDB[selected_train].arrivalMinute
                    ) + TrainDB[selected_train].delayMinutes;

                    TrainDB[selected_train].updatedArrivalHour =
                        (new_arr / 60) % 24;

                    TrainDB[selected_train].updatedArrivalMinute =
                        new_arr % 60;

                    new_dep = Time_To_Minutes(
                        TrainDB[selected_train].departureHour,
                        TrainDB[selected_train].departureMinute
                    ) + TrainDB[selected_train].delayMinutes;

                    TrainDB[selected_train].updatedDepartureHour =
                        (new_dep / 60) % 24;

                    TrainDB[selected_train].updatedDepartureMinute =
                        new_dep % 60;

                    LCD_CMD(0x01);
                    LCD_STR("UPDATE SAVED!");

                    IO0SET = BUZZER;
                    delay_ms(1000);
                    IO0CLR = BUZZER;

                    LCD_CMD(0x01);
                    LCD_STR("1:Dly 2:Plt");
                    LCD_CMD(0xC0);
                    LCD_STR("3:Arr 4:Dep");
                    step = 2;
                }
            }
        }
    }

    admin_menu_flag = 0;
    LCD_CMD(0x01);
}
