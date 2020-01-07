#include	"delayASM16Mhz(v1.1).h"
#include	"uart(v10.0).h"
#include <avr/pgmspace.h>
const char ProgmemString[] PROGMEM  = {"I am in PROGMEM"};
int main(){
	delay100ms();
	uart_init(9600);
	/*
	//########################################
	uart_puts("uint8_t: ");uart_putc('\t');
	uint8_t	ui8=255;
	uart_put_hexu8(ui8);	uart_putc('=');
	uart_putu8(ui8);		uart_putc('\r');
	//########################################
	uart_puts("int8_t: ");uart_putc('\t');
	int8_t		i8=-127;
	uart_put_hexu8(i8);	uart_putc('=');
	uart_put8(i8);		uart_putc('\r');
	uart_putc('\t');
	i8=127;
	uart_put_hexu8(i8);	uart_putc('=');uart_putc(' ');
	uart_put8(i8);		uart_putc('\r');
	//########################################
	uart_puts("uint16_t: ");uart_putc('\t');	
	uint16_t	ui16=65535UL;
	uart_put_hexu16(ui16);	uart_putc('=');
	uart_putu16(ui16);		uart_putc('\r');
	//########################################
	uart_puts("int16_t: ");uart_putc('\t');
	int16_t		i16=-32767L;
	uart_put_hexu16(i16);	uart_putc('=');
	uart_put16(i16);		uart_putc('\r');
	uart_putc('\t');
	i16=32767L;
	uart_put_hexu16(i16);	uart_putc('=');uart_putc(' ');
	uart_put16(i16);		uart_putc('\r');
	//########################################
	uart_puts("uint32_t: ");uart_putc('\t');
	uint32_t	ui32=4294967295UL;
	uart_put_hexu32(ui32);	uart_putc('=');
	uart_putu32(ui32);		uart_putc('\r');
	//########################################
	uart_puts("int32_t: ");uart_putc('\t');
	int32_t		i32=-2147483647L;
	uart_put_hexu32(i32);	uart_putc('=');
	uart_put32(i32);		uart_putc('\r');
	uart_putc('\t');
	i32=2147483647L;
	uart_put_hexu32(i32);	uart_putc('=');uart_putc(' ');
	uart_put32(i32);		uart_putc('\r');
	//########################################
	uart_puts("uint64_t: ");uart_putc('\t');
	uint64_t	ui64=18446744073709551615ULL;
	uart_put_hexu64(ui64);	uart_putc('=');
	uart_putu64(ui64);		uart_putc('\r');
	//########################################
	uart_puts("int64_t: ");uart_putc('\t');
	int64_t		i64=-9223372036854775807LL;
	uart_put_hexu64(i64);	uart_putc('=');
	uart_put64(i64);		uart_putc('\r');
	uart_putc('\t');
	i64=9223372036854775807LL;
	uart_put_hexu64(i64);	uart_putc('=');uart_putc(' ');
	uart_put64(i64);		uart_putc('\r');
	//########################################
	uart_puts("putc:");uart_putc('\t');	
	uart_putc('°');
	uart_puts("±×÷¹²³¯ªº½¼¾çöñ®©");
	uart_putc('\r');//'°' 
	//########################################
	uart_puts("Progmem:");uart_putc('\t');		
	uart_puts_p(ProgmemString);	uart_putc('\r');

	//########################################	
*/
	while(1){
/*
		uart_puts("\r input a number 0 ~ 255: ");
		uart_putu8(uart_getu8());uart_putc('\r');
		uart_puts("\r input a number 0 ~ 65535: ");
		uart_putu16(uart_getu16());uart_putc('\r');
		uart_puts("\r input a number 0 ~ 4294967295: ");
		uart_putu32(uart_getu32());uart_putc('\r');
		uart_puts("\r input a number 0 ~ 18446744073709551615: ");
		uart_putu64(uart_getu64());uart_putc('\r');
		uart_puts("\r input a number -127 ~ 127: ");
		uart_put8(uart_get8());uart_putc('\r');
		uart_puts("\r input a number -32767 ~ 32767: ");
		uart_put16(uart_get16());uart_putc('\r');
		uart_puts("\r input a number -2147483647 ~ 2147483647 : ");
		uart_put32(uart_get32());uart_putc('\r');
		uart_puts("\r input a number -9223372036854775807 ~ 9223372036854775807: ");
		uart_put64(uart_get64());uart_putc('\r');

		uart_puts("\r input a  8-bit binray: ");
		uart_put_binu8(uart_get_binu8());uart_putc('\r');
		uart_puts("\r input a 16-bit binray: ");
		uart_put_binu16(uart_get_binu16());uart_putc('\r');
		uart_puts("\r input a 32-bit binray: ");
		uart_put_binu32(uart_get_binu32());uart_putc('\r');
		uart_puts("\r input a 64-bit binray: ");
		uart_put_binu64(uart_get_binu64());uart_putc('\r');
*/
		//uart_puts("input a hex: ");
		//uart_put_hexu32(uart_get_hexu32());uart_putc('\r');
		
		//uart_puts("input a string then press enter: ");
		//char *s=" ";
		//uart_gets(s);
		//uart_gets_len(s,8);
		//uart_gets_a2b(s,' ','k');
		//uart_puts(s);uart_putc('\r');
		//int16_t my16=0b1000000000000001;
		//float myf=-1.23;
		uart_puts("input a float: ");
		uart_putf(uart_getf(),3);

		
		
		
	uart_putc('\r');
	}
	return 0;
}

