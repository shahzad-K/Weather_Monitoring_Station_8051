#include"temp_header.h"

void delay_ms(int_u16 delay)
{
	char_u8 d;
	for( ; delay>0; --delay)
	{
		d=250;
		while(--d);
		d=247;
		while(--d);
	}
}