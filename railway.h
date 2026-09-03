#ifndef RAILWAY_H
#define RAILWAY_H

#include "types.h" 

#define TOTAL_TRAINS 3 

// Database structure utilizing strict memory sizing
typedef struct
{
    u32 trainNumber;    
    s32 status;                  
    
    char trainName[25];          
    char destination[20];        
    
    u8 arrivalHour;   
    u8 arrivalMinute; 
    u8 departureHour; 
    u8 departureMinute;
    
    u8 updatedArrivalHour;  
    u8 updatedArrivalMinute;
    u8 updatedDepartureHour;
    u8 updatedDepartureMinute;
    
    u8 platform;      
    u8 delayMinutes;  
} TrainInfo_t;  

extern TrainInfo_t TrainDB[TOTAL_TRAINS]; 

#define GREEN_LED      (1 << 4)   
#define YELLOW_LED     (1 << 5)   
#define RED_LED        (1 << 6)   
#define BUZZER         (1 << 7)   

#define ALL_INDICATORS (GREEN_LED | YELLOW_LED | RED_LED | BUZZER) 

#endif
