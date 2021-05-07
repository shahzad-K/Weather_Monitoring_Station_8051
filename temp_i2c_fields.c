#include<reg51.h>
#include"temp_header.h"
#include<intrins.h>

sbit SDA = P2^4;
sbit SCL = P2^3;

void start(void)
{
	SDA=1;
	SCL=1;
	SDA=0;
}

void stop(void)
{
	SDA=0;
	SCL=1;
	SDA=1;
}

void write(char_u8 ch)
{
	char_s8 i;
	for(i=7; i>=0; --i)
	{
		SCL = 0;
		SDA = ch>>i & 1;
		SCL = 1;
	}
}

char_u8 read(void)
{
	char_s8 i;
	char_u8 temp=0;
	for(i=7; i>=0; --i)
	{
		SCL = 1;
		if(SDA==1)
			temp = temp | 1<<i;
		SCL = 0;
	}
	return temp;
}

bit ack(void)
{
	SCL = 0;
	SDA = 1;
	SCL = 1;		//9th clk pulse
	_nop_();
	_nop_();
	_nop_();
	_nop_();	//1us delay *4
	SCL = 0;	//nxt operation
	return SDA==0;
}

bit no_ack(void)
{
	SCL = 0;
	SDA = 1;
	SCL = 1;
	return SDA==1;
}

void byte_write(char_u8 SA, char_u8 MR, char_u8 Data)
{
	start();
	write(SA);
	ack();
	write(MR);
	ack();
	write(Data);
	ack();
	stop();	
	delay_ms(10);
}

char_u8 byte_read(char_u8 SA, char_u8 MR)
{
	char_u8 temp;
	start();
	write(SA);	
	ack();
	write(MR);
	ack();
	start();
	write(SA | 1);
	ack();
	temp = read();
	no_ack();
	stop();
	return temp;
}
