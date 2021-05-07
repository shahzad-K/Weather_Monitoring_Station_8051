#include<reg51.h>
#include"temp_header.h"

void uart_init(void)
{
	SCON = 0x50;		//mode1 REN=1
	TMOD |= 0x20;		//timer1 mode2
	TH1=253;				//set 9600 baud
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

/*void uart_Uint_tx(int_u16 n)
{
	char_u8 i,c,arr[5]={0};
	c = digit_count(n);
	for(i=0; i<c; ++i,n/=10)
		arr[c-i-1] = n%10 + '0';
	for(i=0; i<c; ++i)
		uart_tx(arr[i]);
}

void uart_int_tx(int_s16 n)
{
	if(n < 0)
	{
			n -= 1;
			n = ~n;
			uart_tx('-');
	}
	uart_Uint_tx(n);
}

void uart_float(f_32 n)
{
	int_u32 t1=n, t2=(n-(f_32)t1)*(f_32)100;
	uart_Uint_tx(t1);
	uart_tx('.');
	uart_Uint_tx(t2);
}

char_u8 uart_rx(void)
{
 	while(RI==0);
	RI=0;
	return SBUF;
}

char_s8 uart_str_rx(char_u8 *p)
{
	static char_s8 i=0;
	char_u8 ch;
	ch=uart_rx();
	if(ch=='\r' )
	{
		p[i]='\0';
		i=0;
		return 0;
	}
	p[i]=ch;
	++i;
	return ch;
}
*/
