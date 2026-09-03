//train_dprint.h
#ifndef TRAIN_DPRINT_H
#define TRAIN_DPRINT_H

#include "types.h"
#include "railway.h"

u32 Time_To_Minutes(u8 hour, u8 minute);
u8 Display_Train_Approaching(TrainInfo_t *train);
u8 Str_len(char* str);
void Display_Train_Summary(u8 train_index, u8 page);
void Format_5Digit(u32 value, char* buffer);

#endif
