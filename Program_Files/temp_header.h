#ifndef __temp_header_h__
#define __temp_header_h__

typedef unsigned char char_u8;
typedef char char_s8;
typedef unsigned int int_u16;
typedef int int_s16;
typedef unsigned long int int_u32;
typedef long int int_s32;
typedef float f_32;

extern void delay_ms(int_u16 delay);

//LCD functions
extern void lcd_init(void);
extern void lcd_cmd(char_u8 cmd);
extern void print_str(char_u8 *p);

//UART functions
extern void uart_init(void);
extern void uart_tx(char_u8 ch);
extern void uart_str_tx(char_u8 *p);

extern void INT0_en(void);	//ext. int enable func.
	
//I2C fields & frames
extern void start(void);
extern void stop(void);
extern void write(char_u8 ch);
extern char_u8 read(void);
extern bit ack(void);
extern bit no_ack(void);
extern void byte_write(char_u8 SA, char_u8 MR, char_u8 Data);
extern char_u8 byte_read(char_u8 SA, char_u8 MR);

//I2C frame for EEPROM
extern void eeprom_byte_write(char_u8 SA, char_u8 dH, char_u8 dL, char_u8 * Data);
extern char_u8  eeprom_byte_read(char_u8 SA, char_u8 dH, char_u8 dL);

//EEPROM RD / WR func.
extern void mem_write();
extern void mem_read();

//SPI protocol func for sensors
extern int_u16 read_adc(bit d1, bit d0);
extern char_u8 * read_ldr(void);
extern char_u8 * read_pot(void);

//temperature sensor func.
extern void convert_t(char_u8 SA, char_u8 cmd);
extern char_u8 * read_temperature(void);

//RTC func.
extern void set_rtc();
extern char_u8 * read_rtc(void);

#endif
