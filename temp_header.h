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
extern void lcd_init(void);
extern void lcd_cmd(char_u8 cmd);
extern void cg_ram_init(char_u8 *p, char_u8 n);
extern void print_ch(char_u8 ch);
extern void print_str(char_u8 *p);
extern void print_int(int_u16 n);
extern void print_float(f_32 n);

extern char_u8 str_len(char_u8 *p);

extern char_u8 digit_count(int_u16 n);


extern void uart_init(void);
extern void uart_tx(char_u8 ch);
extern void uart_str_tx(char_u8 *p);
extern char_u8 uart_rx(void);
extern char_s8 uart_str_rx(char_u8 *p);
extern void uart_int_tx(int_s16);
extern void uart_float(f_32 n);

extern void INT0_en(void);
extern void T0_en(void);
	
	
extern void byte_write(char_u8 SA, char_u8 MR, char_u8 Data);
extern char_u8 byte_read(char_u8 SA, char_u8 MR);
extern void start(void);
extern void stop(void);
extern void write(char_u8 ch);
extern char_u8 read(void);
extern bit ack(void);
extern bit no_ack(void);

extern int_u16 read_adc(bit d1, bit d0);

//project

extern void convert_t(char_u8 SA, char_u8 cmd);

extern char_u8 * read_temperature(void);
extern char_u8 * read_ldr(void);
extern char_u8 * read_pot(void);
extern char_u8 * read_rtc(void);

extern void uart_Uint_tx(int_u16 n);
extern void INT0_en(void);
extern void set_rtc();

extern void print_temperature(char_s8 t);
extern void uart_temperature(char_s8 t);
extern void eeprom_byte_write(char_u8 SA, char_u8 dH, char_u8 dL, char_u8 * Data);
extern char_u8  eeprom_byte_read(char_u8 SA, char_u8 dH, char_u8 dL);
extern void mem_write();
extern void mem_read();


#endif