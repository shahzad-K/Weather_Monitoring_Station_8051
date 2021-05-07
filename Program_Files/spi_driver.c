#include"temp_header.h"
#include<reg51.h>

sbit cs = P1^3;
sbit clk = P1^0;
sbit din = P1^1;
sbit dout = P1^2;

int_u16 read_adc(bit d1, bit d0)
{
	int_u16 temp=0;
	char_s8 i;
	
	cs=0;
	clk=0, din=1, clk=1;	//start
	clk=0, din=1, clk=1;	//single-ended
	clk=0, din=1, clk=1;	//D2 dont care
	clk=0, din=d1, clk=1;	//D1
	clk=0, din=d0, clk=1;	//D0
	
	clk=0, clk=1;	//sample
	clk=0, clk=1;	//null bit
	
	for(i=11; i>=0; --i)
	{
		clk=0;
		if(dout==1)
			temp = temp | (1<<i);
		clk=1;
	}
	cs=1;
	return temp;
}

char_u8 * read_ldr(void)
{
	//return read_adc(0,0);
	static char_u8 ldr_val[4];
	char_u8 adc_val= (float)read_adc(0,0)/4095*100;
	ldr_val[0]=adc_val/10+48;
	ldr_val[1]=adc_val%10+48;
	ldr_val[2]='%';
	ldr_val[3]='\0';
	return ldr_val;
}

char_u8 * read_pot(void)
{
	//return (float)(read_adc(0,1)*5)/4095;
	static char_u8 pot_val[6];
	f_32 adc_val=(float)(read_adc(0,1)*5)/4095;
	char_u8 t2=(adc_val-(char_u8)adc_val)*100;
	pot_val[0]=(char_u8)adc_val+48;
	pot_val[1]=('.');
	pot_val[2]=t2/10+48;
	pot_val[3]=t2%10+48;
	pot_val[4]='V';
	pot_val[5]='\0';
	return pot_val;
}
