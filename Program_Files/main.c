#include"temp_header.h"

main()
{
	char_s8 minute_ctr,minute_temp=-1;
	char_u8 *ptr;
	set_rtc();
	convert_t(0x90, 0xEE);	//start temp convert with cmd
	INT0_en();
	uart_init();
	lcd_init();
	
	while(1)
	{
		lcd_cmd(0x80);
		ptr=read_rtc();
	  	print_str("Time: ");
		print_str(ptr);
		
		minute_ctr =(ptr[3]-48)*10 + (ptr[4]-48);
		if(minute_ctr != minute_temp)
		{
			minute_temp=minute_ctr;
			mem_write();
		}
		
		lcd_cmd(0xC0);
		print_str("Temp: ");
		print_str(read_temperature());
			
		lcd_cmd(0x94);
		print_str("LDR: ");
		print_str(read_ldr());
		
		lcd_cmd(0xD4);
		print_str("Pot: ");
		print_str(read_pot());
	}	
}
