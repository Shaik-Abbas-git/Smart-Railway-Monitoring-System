//admin.h
#ifndef ADMIN_H
#define ADMIN_H

#include "types.h"

void Run_Admin_Menu(void);
void LCD_PRINT_INT(u32 num);
s8 Check_Platform_Collision(s8 test_train_id, u32 p_delay, u8 p_plt, u32 p_arr_hhmm, u32 p_dep_hhmm);

#endif
