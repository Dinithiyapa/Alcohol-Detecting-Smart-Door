// main.c
#include <xc.h>
#include "lcd.h"

#define _XTAL_FREQ 16000000

// Sensor and actuator pins
#define ir_sensor PORTBbits.RB4 
#define ach_sensor PORTBbits.RB5 
#define servo_control RC1 
#define led PORTCbits.RC2 

void close(void) 
{ 
    unsigned int i; 
    for (i = 0; i < 50; i++) 
    { 
        PORTCbits.RC1 = 1; 
        __delay_us(3500); 
        PORTCbits.RC1 = 0; 
        __delay_us(16500); 
    } 
} 

void open(void) 
{ 
    unsigned int i; 
    for (i = 0; i < 50; i++) 
    { 
        PORTCbits.RC1 = 1; 
        __delay_us(1500); 
        PORTCbits.RC1 = 0; 
        __delay_us(18500); 
    } 
} 

void main(void) 
{ 
    // UART Configuration
    TXSTA = 0x24;  
    RCSTA = 0x90;  
    SPBRG = 129;   

    // I/O Port Configuration
    TRISC = 0x80;  
    TRISB7 = 0;    
    TRISBbits.TRISB5 = 1; 
    TRISBbits.TRISB4 = 1; 
    TRISC1 = 0; 
    TRISC2 = 0; 
    unsigned int a; 
    TRISD = 0x00; 
    open(); 
    
    Lcd_Start(); 
    led = 0; 

    Lcd_Clear();  
    
    while (1) 
    { 
        Lcd_Clear(); 
        
        if (ir_sensor == 1) 
        { 
            Lcd_Set_Cursor(2, 1); 
            Lcd_Print_String("         "); 
        } 
        else 
        { 
            Lcd_Set_Cursor(1, 1); 
            Lcd_Print_String("Welcome"); 
            __delay_ms(1000); 
            TXREG = 'e'; 
            while (!TXIF)  
                continue; 
            __delay_ms(1000); 
        } 

        __delay_ms(1000);  
        if (ach_sensor == 1) 
        { 
            open(); 
            led = 0; 
        } 
        else 
        { 
            close(); 
            led = 1; 
            Lcd_Set_Cursor(1, 1); 
            Lcd_Print_String("Alcohol"); 
            Lcd_Set_Cursor(2, 1); 
            Lcd_Print_String("Detected"); 
            __delay_ms(1000); 
        }  
    } 
}
