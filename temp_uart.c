#include<reg51.h>
#include"temp_header.h"

void uart_init(void)
{
	SCON = 0x50;		//mode1 REN=1
	TMOD |= 0x20;		//timer1 mode2
	TH1=253;		//set 9600 baud
	TR1=1;
}

void uart_tx(char_u8 ch)
{
  	SBUF = ch;
	while(TI == 0);
	TI=0;
}

void uart_str_tx(char_u8 *p)
{
	while(*p != '\0')
	{
		uart_tx(*p);
		++p;
	}
}
