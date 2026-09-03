#ifndef RTC_h
#define RTC_h

extern const char* day_names[7];
void RTC_INIT(void);
void digi_2format(int value,char *str);
void Display_state(void);
int Get_Numeric_Input(char* prompt, int min_val, int max_val);
void Set_RTC_Date_Time(void);

#endif
