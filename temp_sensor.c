#include<reg51.h>
#include"temp_header.h"

sbit A0 = P2^5;
sbit A1 = P2^6;
sbit A2 = P2^7;

//Temperature Sensor functions
void convert_t(char_u8 SA, char_u8 cmd)
{
	A0=A1=A2=0;
	start();	//temp convert start
	write(SA);
	ack();
	write(cmd);	//strt cmd
	ack();
	stop();		//end
}

char_u8 * read_temperature(void)
{
	//DS1621 control code 1001 a2 a1 a0 r/w
	char_u8 tempH;
	char_s8 t;
	static char_u8 temp_arr[7]=' ';
	start();
	write(0x90);	//send 0x90
	ack();
	write(0xAA);	//read temp. cmd
	ack();
	start();
	write(0x90 | 1);	//send 0x91 for read
	ack();
	tempH = read();
	no_ack();
	stop();
	
	if(tempH==128)	//temp.range of -55 to +127
	{
		lcd_cmd(0xC7);
		print_str("ERROR");
		return 0;
	}
	
	t=tempH;
	if(t<0)
	{
		t -= 1;
		t = ~t;
		temp_arr[0]=('-');
	}
	else
		temp_arr[0]=(' ');
	temp_arr[1]=(t/100 +48);
	temp_arr[2]=(((t/10)%10) +48);	
	temp_arr[3]=(t%10 +48);
	temp_arr[4]=(0xDF);		//ascii of degree symbol
	temp_arr[5]=('C');
	temp_arr[6]=('\0');
	return temp_arr;
}
