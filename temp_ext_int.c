#include"temp_header.h"
#include<reg51.h>

sbit SW = P3^2;

void INT0_en(void)
{
	//EA=EX0=1;
	IE=0x81;		//setting ext. int. 0
}

void INT0_handler(void) interrupt 0
{
	while(SW==0);
	uart_str_tx("ID   Time    Temp  LDR  POT\r\n");
	mem_read();
	uart_str_tx("\r\n\r\n");
}
