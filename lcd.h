// lcd.h
#ifndef LCD_H
#define LCD_H

// Function prototypes for LCD control
void Lcd_SetBit(char data_bit);
void Lcd_Cmd(char a);
void Lcd_Clear(void);
void Lcd_Set_Cursor(char a, char b);
void Lcd_Start(void);
void Lcd_Print_Char(char data);
void Lcd_Print_String(char *a);

#endif // LCD_H
