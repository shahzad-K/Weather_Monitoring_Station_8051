#include"temp_header.h"
#include<reg51.h>

#define LCD_OUT P0
sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;

void lcd_init(void)
{
	delay_ms(2);
	lcd_cmd(0x38);		//8-bit mode
	lcd_cmd(0x01);		//clear lcd
	lcd_cmd(0x0C);		//cursor off
}

void lcd_cmd(char_u8 cmd)
{
	LCD_OUT = cmd;
	RS = 0;		//0 - cmd ; 1 - data
	RW = 0;		//0 - wr ; 1 - rd
	EN = 1;		// high to low pulse
	delay_ms(2);
	EN = 0;
}

void print_str(char_u8 *p)
{
	RS = 1;
	RW = 0;
	while(*p != '\0')
	{
		LCD_OUT = *p;	//write data on LCD port
		
		EN = 1;
		delay_ms(2);
		EN = 0;
		++p;
	}
}
