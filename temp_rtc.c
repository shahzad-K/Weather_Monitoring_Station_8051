#include"temp_header.h"
	
void set_rtc(void)	//setting RTC
{
	//0xD0 Slave add. of RTC
	byte_write(0xD0, 0x2, 0x71);		//0x2 mem_add for hrs
	byte_write(0xD0, 0x1, 0x59);		//0x1 mem_add for mins
	byte_write(0xD0, 0x0, 0x0);		//0x0 mem_add for sec
}	

char_u8 * read_rtc(void)
{
	static char_u8 time[12];
	char_u8 hh,mm,ss,hour,minutes,seconds;
	hh=byte_read(0xD0, 0x2);
	mm=byte_read(0xD0, 0x1);
	ss=byte_read(0xD0, 0x0);
	
	hour = ((hh & 0x1F)>>4)*10 + (hh & 0x0F);		//convert BCD into decimal
	minutes = (((mm & 0xF0)>>4)*10) +  (mm & 0x0F);		//convert BCD into decimal
	seconds = (((ss & 0xF0)>>4)*10) +  (ss & 0x0F);		//convert BCD into decimal
	
	time[0] = hour/10+48;		//store by converting decimal into ascii value
	time[1] = hour%10+48;
	time[2] = '-';
	
	time[3] = minutes/10+48;
	time[4] = minutes%10+48;
	time[5] = '-';
	
	time[6] = seconds/10+48;
	time[7] = seconds%10+48;
	time[8] = ' ';
	if((hh>>5&1)==1)		//check 5th bit of hh is PM or AM
		time[9] = 'P';
	else
		time[9] = 'A';
	time[10] = 'M';
	time[11] = '\0';
	
	return time;
}
