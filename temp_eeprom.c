#include<reg51.h>
#include"temp_header.h"

sbit SDA = P2^4;
sbit SCL = P2^3;

static char_u8 log_count=0;

void eeprom_byte_write(char_u8 SA, char_u8 dH, char_u8 dL, char_u8 * Data)
{
	char_u8 i;
	start();
	write(SA);
	ack();
	write(dH);
	ack();
	write(dL);
	ack();
	for(i=0; ; ++i)
	{
		write(Data[i]);
		ack();
		if(Data[i]=='\0')
			break;
	}
	stop();	
	delay_ms(10);
}

char_u8  eeprom_byte_read(char_u8 SA, char_u8 dH, char_u8 dL)
{
	char_u8 temp;
	start();
	write(SA);	
	ack();
	write(dH);
	ack();
	write(dL);
	ack();
	
	start();
	write(SA | 1);
	ack();
	temp = read();
	no_ack();
	stop();
	return temp;
}

void mem_write()
{
	//1010 0 a1 a0 r/w
	char_u8 i,j, *ptr;
	static char_u8 log_arr[29];
	static int_u16 dword=0;
	++log_count;
	
	log_arr[0]=log_count/10+48;
	log_arr[1]=log_count%10+48;
	log_arr[2]=' ';
	
	ptr=read_rtc();
	for(i=3,j=0;	i<8; ++i,++j)
		log_arr[i]=ptr[j];
	log_arr[8]=' ';
	log_arr[9]=ptr[9];
	log_arr[10]=ptr[10];
	log_arr[11]=' ';
	
	ptr=read_temperature();
	for(i=12,j=0;	i<18; ++i,++j)
		log_arr[i]=ptr[j];
	log_arr[18]=' ';
	
	ptr=read_ldr();
	for(i=19,j=0;	i<22; ++i,++j)
		log_arr[i]=ptr[j];
	log_arr[22]=' ';
	
	ptr=read_pot();
	for(i=23,j=0;	i<28; ++i,++j)
		log_arr[i]=ptr[j];
	log_arr[28]='\0';
	
	eeprom_byte_write(0xA0, ((dword << 7) >> 8), ((dword << 7) & 0x80), log_arr);
	++dword;
}

void mem_read()
{
	char_u8 i=log_count, dH, dL, temp;
	int_u16 dword=0;
		
	while(i>0)
	{
		dH = (dword<<7) >> 8;
		dL = (dword<<7) & 0x80;
		for( ; ; ++dL)
		{
			temp = eeprom_byte_read(0xA0, dH, dL);
			if(temp == '\0')
				break;
			uart_tx(temp);
		}
		--i;
		++dword;
		uart_tx('\r');
	}
}
