#include "railway.h"

//main train databsse
TrainInfo_t TrainDB[TOTAL_TRAINS] = 
{
    // Train 1
    {12627, 0, "Karnataka Express", "New Delhi", 6, 30, 6, 35, 6, 30, 6, 35, 1, 0},
    
    // Train 2 
    {12028, 1, "Shatabdi Express", "Chennai", 7, 15, 7, 20, 7, 15, 7, 20, 2, 0}, 
    
    // Train 3 (Delayed)
    {12785, 1, "Kacheguda Express", "Hyderabad", 8, 00, 8, 05, 8, 20, 8, 25, 3, 20} 
};
