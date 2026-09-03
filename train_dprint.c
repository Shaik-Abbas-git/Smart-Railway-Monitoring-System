//train_dprint.c
#include "railway.h"
#include "lcd.h"
#include "rtc.h"
#include "train_dprint.h"
#include "admin.h"


// Convert time into total minutes for easy comparison
u32 Time_To_Minutes(u8 hour, u8 minute)
{
    return (hour * 60) + minute;
}


// Display the train schedule during normal monitoring
void Display_Train_Summary(u8 train_index, u8 page)
{
    char temp_str[16];
    u8 i;
    u8 d_mins = 0;

    u32 live_mins;
    u32 dep_mins;
    s32 diff;

    LCD_CMD(0x01);
    LCD_CMD(0x80);

    LCD_PRINT_INT(TrainDB[train_index].trainNumber);
    LCD_DATA(' ');

    // Display up to 9 characters of the train name
    for (i = 0; i < 9; i++)
    {
        if (TrainDB[train_index].trainName[i] == '\0')
            break;

        LCD_DATA(TrainDB[train_index].trainName[i]);
    }

    live_mins = Time_To_Minutes(HOUR, MIN);
    dep_mins = Time_To_Minutes(
        TrainDB[train_index].updatedDepartureHour,
        TrainDB[train_index].updatedDepartureMinute
    );

    diff = dep_mins - live_mins;

    // Handle time comparison across midnight
    if (diff < -720)
        diff += 1440;

    LCD_CMD(0xC0);

    if (diff < 0)
    {
        LCD_STR(" -- DEPARTED -- ");
    }
    else
    {
        if (page == 0)
        {
            LCD_STR("Arr:");

            digi_2format(
                TrainDB[train_index].updatedArrivalHour,
                temp_str
            );
            LCD_STR(temp_str);
            LCD_DATA(':');

            digi_2format(
                TrainDB[train_index].updatedArrivalMinute,
                temp_str
            );
            LCD_STR(temp_str);

            LCD_STR(" Plt:");
            LCD_DATA(TrainDB[train_index].platform + '0');
        }
        else
        {
            // Display up to 9 characters of the destination
            for (i = 0; i < 9; i++)
            {
                if (TrainDB[train_index].destination[i] == '\0')
                    break;

                LCD_DATA(TrainDB[train_index].destination[i]);
            }

            // Clear remaining positions
            for (; i < 9; i++)
                LCD_DATA(' ');

            LCD_CMD(0xC9);

            if (TrainDB[train_index].status == 1)
            {
                LCD_STR(" D:+");

                d_mins = TrainDB[train_index].delayMinutes;

                if (d_mins >= 100)
                {
                    LCD_DATA((d_mins / 100) % 10 + '0');
                }
                else
                {
                    LCD_DATA(' ');
                }

                LCD_DATA((d_mins / 10) % 10 + '0');
                LCD_DATA((d_mins % 10) + '0');
            }
            else
            {
                LCD_STR("ON TIME");
            }
        }
    }
}


// Calculate the length of a string
u8 Str_len(char *str)
{
    u8 len = 0;

    while (str[len] != '\0')
    {
        len++;
    }

    return len;
}


// Convert a number into a 5-digit string
void Format_5Digit(u32 value, char *buffer)
{
    buffer[0] = (value / 10000) + '0';
    buffer[1] = ((value / 1000) % 10) + '0';
    buffer[2] = ((value / 100) % 10) + '0';
    buffer[3] = ((value / 10) % 10) + '0';
    buffer[4] = (value % 10) + '0';
    buffer[5] = '\0';
}


// Display the approaching train with scrolling name
u8 Display_Train_Approaching(TrainInfo_t *train)
{
    char temp_str[4];
    char temp_str_5[6];

    // Static variables retain their values between function calls
    static u8 scroll_pos = 0;
    static u8 speed_counter = 0;
    static u8 full_scrolls = 0;
    static u32 last_train_id = 99999;

    u8 i, char_idx, name_len;

    // Reset the scrolling state when a new train is displayed
    if (train->trainNumber != last_train_id)
    {
        scroll_pos = 0;
        full_scrolls = 0;
        last_train_id = train->trainNumber;
        LCD_CMD(0x01);
    }

    // Line 1: Display train number and scrolling train name
    LCD_CMD(0x80);

    Format_5Digit(train->trainNumber, temp_str_5);
    LCD_STR(temp_str_5);
    LCD_STR(" ");

    LCD_CMD(0x86);
    name_len = Str_len(train->trainName);

    // Create a 10-character sliding window for the train name
    for (i = 0; i < 10; i++)
    {
        char_idx = scroll_pos + i;

        if (char_idx >= (name_len + 3))
        {
            char_idx = char_idx - (name_len + 3);
        }

        if (char_idx < name_len)
        {
            LCD_DATA(train->trainName[char_idx]);
        }
        else
        {
            LCD_DATA(' ');
        }
    }

    // Line 2: Alternate between train details and live time
    LCD_CMD(0xC0);

    if (SEC % 4 < 2)
    {
        digi_2format(train->platform, temp_str);
        LCD_DATA(temp_str[1]);
        LCD_STR(" ");

        digi_2format(train->updatedArrivalHour, temp_str);
        LCD_STR(temp_str);
        LCD_DATA(':');

        digi_2format(train->updatedArrivalMinute, temp_str);
        LCD_STR(temp_str);
        LCD_STR(" ");

        digi_2format(train->updatedDepartureHour, temp_str);
        LCD_STR(temp_str);
        LCD_DATA(':');

        digi_2format(train->updatedDepartureMinute, temp_str);
        LCD_STR(temp_str);
        LCD_STR(" ");

        digi_2format(train->delayMinutes, temp_str);
        LCD_STR(temp_str);
    }
    else
    {
        LCD_STR("Time: ");

        digi_2format(HOUR, temp_str);
        LCD_STR(temp_str);
        LCD_DATA(':');

        digi_2format(MIN, temp_str);
        LCD_STR(temp_str);
        LCD_DATA(':');

        digi_2format(SEC, temp_str);
        LCD_STR(temp_str);
        LCD_STR("  ");
    }

    // Control the scrolling speed
    speed_counter++;

    if (speed_counter > 1)
    {
        scroll_pos++;
        speed_counter = 0;

        // Track completed scrolling cycles
        if (scroll_pos >= (name_len + 3))
        {
            scroll_pos = 0;
            full_scrolls++;
        }
    }

    // Tell the main loop when this train's animation is complete
    if (full_scrolls >= 2)
    {
        full_scrolls = 0;
        return 1;
    }

    return 0;
}
