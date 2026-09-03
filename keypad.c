#include <LPC21xx.h>
#include "delay.h"

char key_map[4][4] = 
{
   {'7', '8', '9', '/'},
   {'4', '5', '6', '*'},
   {'1', '2', '3', '-'},
   {'C', '0', '=', 'D'}
};

void KEYPAD_INIT(void) 
{
    //Set Rows as OUTPUT (1). Columns remain INPUT (0)
    IODIR1 |= (0x0F << 16); 
}

void Scan_Row(unsigned int row) 
{
    //Make ALL row valves OFF (Set them to 1 / HIGH)
    IOSET1 = (0x0F << 16);
    
    IOCLR1 = (1 << (16 + row));
}

int Check_Columns(void) 
{
    unsigned int cols;
    
    // Read the full port, shift it so Column 0 is at bit 0, and mask the rest
    cols = (IOPIN1 >> 20) & 0x0F; 

    if (cols == 0x0E) return 0; // 1110 -> Column 0 is pressed
    if (cols == 0x0D) return 1; // 1101 -> Column 1 is pressed
    if (cols == 0x0B) return 2; // 1011 -> Column 2 is pressed
    if (cols == 0x07) return 3; // 0111 -> Column 3 is pressed
	
    
    return -1; // 1111 -> No button pressed
}

char Read_Keypad(void) 
{
    int r, c;
    
    for (r = 0; r < 4; r++) 
    {
        Scan_Row(r);          
        c = Check_Columns();   
        
        if (c != -1) //if Pressed
        {
            delay_ms(20); // Debounce
            
            if (Check_Columns() == c) 
            {
                while (Check_Columns() == c); 
                
                return key_map[r][c]; 
            }
        }
    }
    
    return '\0'; // Return null if nothing is pressing
}
