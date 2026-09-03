// indicator.c
#include <LPC21XX.H>
#include "indicator.h"
#include "railway.h"


void Update_Indicators(int train_id, int is_arriving)
{
    if (is_arriving == 1)
    {
        // Approaching train: Yellow ON, Green and Red OFF
        IO0CLR = (GREEN_LED | RED_LED);
        IO0SET = YELLOW_LED;

        if (SEC % 2 == 0)
            IO0SET = BUZZER;
        else
            IO0CLR = BUZZER;
    }
    else
    {
        // Normal state: Yellow and Buzzer OFF
        IO0CLR = (YELLOW_LED | BUZZER);

        if (TrainDB[train_id].status == 1)
        {
            IO0CLR = GREEN_LED;
            IO0SET = RED_LED;
        }
        else
        {
            IO0CLR = RED_LED;
            IO0SET = GREEN_LED;
        }
    }
}
