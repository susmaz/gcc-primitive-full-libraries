#include <avr/io.h>
#include <avr/pgmspace.h>
#ifndef UART_H
#define UART_H
void uart_delay(uint32_t time)	{
	while(time){
	   asm volatile (    // _delay_ms(1);
		"    ldi  r18, 21"	"\n"
		"    ldi  r19, 199"	"\n"
		"1:  dec  r19"	"\n"
		"    brne 1b"	"\n"
		"    dec  r18"	"\n"
		"    brne 1b"	"\n"
		);
		time--;
	}
}

	
//'\n'=10=0x0A=LF  (Line Feed)
//'\r'=13=0x0D=CR  (Carriage Return)
#if defined(__AVR_ATmega328__)
void uart_init(int16_t 		baud)	{
	UCSR0B|=(1<<TXEN0)|(1<<RXEN0);
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
	UBRR0H=(uint8_t)((F_CPU/16/baud-1)>>8);
	UBRR0L=(uint8_t) (F_CPU/16/baud-1);
	uart_delay(4);
}
void uart_putc(unsigned char c )	{	
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = c;	
	uart_delay(2);
}	
uint8_t uart_getc(){
	while (!(UCSR0A & (1<<RXC0)));// RXC=Bit7of UCSRA ; RXC: USART Receive Complete
	return UDR0;
	}
#endif
#if defined(__AVR_ATmega8__  )
	void uart_init(int16_t 		baud)	{
	UCSRB |= (1<<TXEN) | ( 1<<RXEN);
	UCSRC |= (1<<URSEL) | (1<<UCSZ0)| (1<<UCSZ1);// Use 8-bit character sizes
	UBRRH = (uint8_t)((F_CPU/16/baud-1)>>8);
	UBRRL = (uint8_t) (F_CPU/16/baud-1);
	uart_delay(4);
}
void uart_putc(unsigned char c )	{	
	while (!(UCSRA & (1<<UDRE)));
	UDR = c;	
	uart_delay(2);
}	
uint8_t uart_getc(){
	while (!(UCSRA & (1<<RXC)));// Bit 7 of UCSRA = RXC: USART Receive Complete
	return UDR;
	}
#endif
void uart_puts		 (char* 	 str){
  while( *str )
    uart_putc( *str++ );
}
void uart_puts_p	 (const char*str){ //need  #include <avr/pgmspace.h>
    while(pgm_read_byte(str) != 0)
        uart_putc(pgm_read_byte(str++));
}
void uart_putu8		 (uint8_t   data){ //uint8_t : 0 ~ 255	
	if(data>99)	uart_putc('0'+(data/100));
	if(data>9)	uart_putc('0'+(data%100)/10);
	uart_putc('0'+(data%100)%10);
}
void uart_putu16	 (uint16_t  data){ //uint16_t: 0 ~ 65535
if(data>9999)	uart_putc('0'+	data/10000					);
if(data>999)	uart_putc('0'+	(data%10000)/1000				);
if(data>99)		uart_putc('0'+	((data%10000)%1000)/100			);
if(data>9)		uart_putc('0'+	(((data%10000)%1000)%100)/10	);
uart_putc('0'+data%10);
}
void uart_putu32	 (uint32_t  data){ //uint32_t: 0 ~ 4294967295
	if(data>999999999L)	uart_putc('0'+			data/1000000000UL);
	if(data>99999999L)	uart_putc('0'+(			data%1000000000UL)/100000000UL);
	if(data>9999999L)	uart_putc('0'+((		data%1000000000UL)%100000000UL)/10000000UL);
	if(data>999999L)	uart_putc('0'+(((		data%1000000000UL)%100000000UL)%10000000UL)/1000000UL);
	if(data>99999L)		uart_putc('0'+((((		data%1000000000UL)%100000000UL)%10000000UL)%1000000UL)/100000UL);
	if(data>9999L)		uart_putc('0'+(((((		data%1000000000UL)%100000000UL)%10000000UL)%1000000UL)%100000UL)/10000UL);
	if(data>999)		uart_putc('0'+((((((	data%1000000000UL)%100000000UL)%10000000UL)%1000000UL)%100000UL)%10000UL)/1000UL);
	if(data>99)			uart_putc('0'+(((((((	data%1000000000UL)%100000000UL)%10000000UL)%1000000UL)%100000UL)%10000UL)%1000UL)/100);
	if(data>9)			uart_putc('0'+((((((((	data%1000000000UL)%100000000UL)%10000000UL)%1000000UL)%100000UL)%10000UL)%1000UL)%100)/10);
						uart_putc('0'+(((((((((	data%1000000000UL)%100000000UL)%10000000UL)%1000000UL)%100000UL)%10000UL)%1000UL)%100)%10));
}
void uart_putu64	 (uint64_t  data){ //uint64_t: 0 ~ 18 446 744 073 709 551 615
	if(data>9999999999999999999ULL)	uart_putc('0'+					data/10000000000000000000ULL);
	if(data>999999999999999999ULL)	uart_putc('0'+(					data%10000000000000000000ULL)/1000000000000000000ULL);
	if(data>99999999999999999ULL)	uart_putc('0'+((				data%10000000000000000000ULL)%1000000000000000000ULL)/100000000000000000ULL);
	if(data>9999999999999999ULL)	uart_putc('0'+(((				data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)/10000000000000000ULL);
	if(data>999999999999999ULL)		uart_putc('0'+((((				data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)/1000000000000000ULL);
	if(data>99999999999999ULL)		uart_putc('0'+(((((				data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)/100000000000000ULL);
	if(data>9999999999999ULL)		uart_putc('0'+((((((			data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)/10000000000000ULL);
	if(data>999999999999ULL)		uart_putc('0'+(((((((			data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)/1000000000000ULL);
	if(data>99999999999ULL)			uart_putc('0'+((((((((			data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)/100000000000ULL);
	if(data>9999999999ULL)			uart_putc('0'+(((((((((			data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)/10000000000ULL);
	if(data>999999999ULL)			uart_putc('0'+((((((((((		data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)/1000000000ULL);
	if(data>99999999ULL)			uart_putc('0'+(((((((((((		data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)/100000000ULL);
	if(data>9999999ULL)				uart_putc('0'+((((((((((((		data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)/10000000ULL);
	if(data>999999ULL)				uart_putc('0'+(((((((((((((		data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)%10000000ULL)/1000000ULL);
	if(data>99999ULL)				uart_putc('0'+((((((((((((((	data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)%10000000ULL)%1000000ULL)/100000ULL);
	if(data>9999ULL)				uart_putc('0'+(((((((((((((((	data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)%10000000ULL)%1000000ULL)%100000ULL)/10000ULL);
	if(data>999ULL)					uart_putc('0'+((((((((((((((((	data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)%10000000ULL)%1000000ULL)%100000ULL)%10000ULL)/1000UL);
	if(data>99ULL)					uart_putc('0'+(((((((((((((((((	data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)%10000000ULL)%1000000ULL)%100000ULL)%10000ULL)%1000UL)/100);
	if(data>9ULL)					uart_putc('0'+((((((((((((((((((data%10000000000000000000ULL)%1000000000000000000ULL)%100000000000000000ULL)%10000000000000000ULL)%1000000000000000ULL)%100000000000000ULL)%10000000000000ULL)%1000000000000ULL)%100000000000ULL)%10000000000ULL)%1000000000ULL)%100000000ULL)%10000000ULL)%1000000ULL)%100000ULL)%10000ULL)%1000UL)%100)/10);
	
	uart_putc('0'+data%10);
}
void uart_put8		 (int8_t    data){ //int8_t	: -127 ~ 127	
	if(data<0){data=-data;uart_putc('-');}
	uart_putu8(data);
}
void uart_put16		 (int16_t   data){ //int16_t	: -32767 ~ 32767
	if(data<0){data=-data;uart_putc('-');}
	uart_putu16(data);
}
void uart_put32		 (int32_t   data){ //int32_t	: -2147483647 ~ 2147483647
	if(data<0){data=-data;uart_putc('-');}
	uart_putu32(data);
}
void uart_put64		 (int64_t   data){ //int64_t	: -9223372036854775807 ~ 9223372036854775807
	if(data<0){data=-data;uart_putc('-');}
	uart_putu64(data);
}
void uart_put_binu8_ (uint8_t   data){
	uart_putc((data & (1<<7))?'1':'0');
	uart_putc((data & (1<<6))?'1':'0');
	uart_putc((data & (1<<5))?'1':'0');
	uart_putc((data & (1<<4))?'1':'0');
	uart_putc((data & (1<<3))?'1':'0');
	uart_putc((data & (1<<2))?'1':'0');
	uart_putc((data & (1<<1))?'1':'0');
	uart_putc((data & (1<<0))?'1':'0');
}

void uart_put_binu8	 (uint8_t   data){
	uart_putc('0');
	uart_putc('b');
	uart_put_binu8_(data);
}

void uart_put_binu16_(uint16_t  data){
    
    uart_put_binu8_((uint8_t)(data>>8));
	uart_put_binu8_((uint8_t)data);
}
void uart_put_binu16 (uint16_t  data){
	uart_putc('0');
	uart_putc('b');
	uart_put_binu16_(data);
}
void uart_put_binu32_(uint32_t  data){
    uart_put_binu16_((uint16_t)(data>>16));
	uart_put_binu16_((uint16_t)data);
}
void uart_put_binu32 (uint32_t  data){
	uart_putc('0');
	uart_putc('b');
	uart_put_binu32_(data);
}
void uart_put_binu64_(uint64_t  data){
    uart_put_binu32_((uint32_t)(data>>32));
	uart_put_binu32_((uint32_t)data);
}
void uart_put_binu64 (uint64_t  data){
	uart_putc('0');
	uart_putc('b');
	uart_put_binu64_(data);
}

void uart_put_hexu8_ (uint8_t   data){
	uart_putc(((data/0x10)>9)?(data/0x10)+55:(data/0x10)+48);
	uart_putc(((data%0x10)>9)?(data%0x10)+55:(data%0x10)+48);
}	

void uart_put_hexu8	 (uint8_t   data){
	uart_putc('0');
	uart_putc('x');
	uart_put_hexu8_(data);
}

void uart_put_hexu16_(uint16_t  data){    
    uart_put_hexu8_((uint8_t)(data>>8));
	uart_put_hexu8_((uint8_t)data);
}
void uart_put_hexu16 (uint16_t  data){
	uart_putc('0');
	uart_putc('x');
	uart_put_hexu16_(data);
}
void uart_put_hexu32_(uint32_t  data){
    uart_put_hexu16_((uint16_t)(data>>16));
	uart_put_hexu16_((uint16_t)data);
}
void uart_put_hexu32 (uint32_t  data){
	uart_putc('0');
	uart_putc('x');
	uart_put_hexu32_(data);
}
void uart_put_hexu64_(uint64_t  data){
    uart_put_hexu32_((uint32_t)(data>>32));
	uart_put_hexu32_((uint32_t)data);
}
void uart_put_hexu64 (uint64_t  data){
	uart_putc('0');
	uart_putc('x');
	uart_put_hexu64_(data);
}
void uart_putf(float f,uint8_t decimal){
	char digs[12],reversed[12];
	uint8_t a=0,b,neg=0;
	if(f<0){neg=1;f=-f;}
	if(decimal){
		int16_t res = 1;
		for (uint8_t i = 0; i < decimal; i++)
			res *= 10;
		f*=res;
		for(a=0;a<decimal;a++){
			b=(uint8_t)(f-10*((long)(f/10)));//b=(uint8_t)fmod_(f,10);
			digs[a]=b+48;
			f/=10;
		}
		digs[a]='.';
		a++;
	}
	do{
		b=(uint8_t)(f-10*((long)(f/10)));
		digs[a]=b+48;
		f/=10;
		a++;
	}while((int)f&&a<11);
	 // Reverse the digits into most significant to least significant
	if(neg){
		reversed[0]='-';
		for(b=1;b<a+neg;b++)
			reversed[b]=digs[a-b];
		a+=1;// Extend the length of the string by 1 due to - sign
	}
	else for(b=0;b<a;b++)
		reversed[b]=digs[a-b-1];
	reversed[a]='\0';
	uart_puts((char*)reversed);
}
//########################################################################################
void 	  uart_gets(char *s){
	while(((*s)=uart_getc())!='\r')  //'\r'=13=0x0D=CR  (Carriage Return)
		s++;
	*s=0;//append'\0'to produce proper c string
}
void	  uart_gets_len(char s[255], uint8_t MaxLen){
	uint8_t c;
	uint16_t len = 0;
	c=uart_getc();
	while((c!='\r')&&(len<MaxLen)){
		if(c!='\r'){s[len]=c;}// do not collect \r char
		len++;
		c=uart_getc();
	}
	s[MaxLen]='\0';//append '\0' to produce proper c string
}

void	  uart_gets_a2b(char s[255],char a,char b){
	uint8_t c=uart_getc();
	while((c!=a))
		c=uart_getc();
	if((c==a))
		c=uart_getc();
	uint8_t len = 0;
	while((c!='\n')&&(c!=b)){
		if(c!='\r'){s[len]=c;}// do not collect \r char
		len++;
		c=uart_getc();
	}
	s[len]='\0';//append '\0' to produce proper c string
}

uint8_t   uart_getu8 	  (){ //uint8_t :0 ~ 255	
	char s[4];
	uint8_t ui8=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 3)){
		if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui8=ui8*10+(s[k]-'0');
		k++;
	}
	return ui8;
}
uint16_t  uart_getu16	  (){ //uint16_t:0 ~ 65 535
	char s[6];
	uint16_t ui16=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 5)){
		if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui16=ui16*10+(s[k]-'0');
		k++;
	}
	return ui16;
}
uint32_t  uart_getu32	  (){ //uint32_t:0 ~ 4 294 967 295
	char s[11];
	uint32_t ui32=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 10)){
		if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui32=ui32*10+(s[k]-'0');
		k++;
	}
	return ui32;
} 


uint64_t  uart_getu64	  (){ //uint64_t:0 ~ 18 446 744 073 709 551 615
	char s[21];
	uint64_t ui64=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 20)){
		if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui64=ui64*10+(s[k]-'0');
		k++;
	}
	return ui64;
} 
int8_t    uart_get8  	  (){ //int8_t  :-127 ~ 127	
	int8_t sign=1;
	char s[4];
	int8_t i8=0;int8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 3)){
		if ((s[0] =='-')&&(sign==1)){sign=-1;k--;}else
			if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
	}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		i8=i8*10+(s[k]-'0');
		k++;
	}
	return sign*i8;
}
int16_t   uart_get16 	  (){ //int16_t :-32767 ~ 32767
	int8_t sign=1;
	char s[6];
	int16_t i16=0;int8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 5)){
		if ((s[0] =='-')&&(sign==1)){sign=-1;k--;}else
			if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
	}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		i16=i16*10+(s[k]-'0');
		k++;
	}
	return sign*i16;
}
int32_t   uart_get32 	  (){ //int32_t :-2147483647 ~ 2147483647 
	int8_t sign=1;
	char s[11];
	int32_t i32=0;int8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 10)){
		if ((s[0] =='-')&&(sign==1)){sign=-1;k--;}else
			if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
	}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		i32=i32*10+(s[k]-'0');
		k++;
	}
	return sign*i32;
} 


int64_t   uart_get64 	  (){ //int64_t :-9223372036854775807 ~ 9223372036854775807
	int8_t sign=1;
	char s[21];
	int64_t i64=0;int8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 20)){
		if ((s[0] =='-')&&(sign==1)){sign=-1;k--;}else
			if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
	}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		i64=i64*10+(s[k]-'0');
		k++;
	}
	return sign*i64;
} 
uint8_t   uart_get_binu8  (){	
	char s[8];
	uint8_t ui8=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 9)){
		if((s[k]<'0')||(s[k]>'1')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui8=ui8*2+(s[k]-'0');
		k++;
	}
	return ui8;
}


uint16_t  uart_get_binu16 (){ 
	char s[16];
	uint16_t ui16=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 17)){
		if((s[k]<'0')||(s[k]>'1')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui16=ui16*2+(s[k]-'0');
		k++;
	}
	return ui16;
}
uint32_t  uart_get_binu32 (){ 
	char s[32];
	uint32_t ui32=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 33)){
		if((s[k]<'0')||(s[k]>'1')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui32=ui32*2+(s[k]-'0');
		k++;
	}
	return ui32;
} 


uint64_t  uart_get_binu64 (){ 
	char s[64];
	uint64_t ui64=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 65)){
		if((s[k]<'0')||(s[k]>'1')) return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui64=ui64*2+(s[k]-'0');
		k++;
	}
	return ui64;
} 
uint8_t   uart_get_hexu8  (){	
	char s[2];
	uint8_t ui8=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 2)){
		if((s[k]>'a'-1)&&(s[k]<'f'+1))	s[k]=s[k]-'a'+':';
		if((s[k]>'A'-1)&&(s[k]<'F'+1))	s[k]=s[k]-'A'+':';
		if((s[k]<'0')||(s[k]>'?')) 
			return 0;
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui8=ui8*16+(s[k]-'0');
		k++;
	}
	return ui8;
}
uint16_t  uart_get_hexu16 (){	
	char s[4];
	uint16_t ui16=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 4)){
		if((s[k]>'a'-1)&&(s[k]<'f'+1))	s[k]=s[k]-'a'+':';
		if((s[k]>'A'-1)&&(s[k]<'F'+1))	s[k]=s[k]-'A'+':';
		if((s[k]<'0')||(s[k]>'?'))		return 0;
		k++;
	}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui16=ui16*16+(s[k]-'0');
		k++;
	}
	return ui16;
}




uint32_t  uart_get_hexu32 (){	
	char s[9];//i dont know why s[8] ERROR over 0FFFFFFFF
	uint32_t ui32=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 8)){
		if((s[k]>'a'-1)&&(s[k]<'f'+1))	s[k]=s[k]-'a'+':';
		if((s[k]>'A'-1)&&(s[k]<'F'+1))	s[k]=s[k]-'A'+':';
		if((s[k]<'0')||(s[k]>'?')) {
			return 0;
		}
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui32=ui32*16+(s[k]-'0');
		k++;
	}
	return ui32;
}



uint64_t  uart_get_hexu64 (){	
	char s[16];
	uint64_t ui64=0;uint8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (k < 16)){
		if((s[k]>'a'-1)&&(s[k]<'f'+1))	s[k]=s[k]-'a'+':';
		if((s[k]>'A'-1)&&(s[k]<'F'+1))	s[k]=s[k]-'A'+':';
		if((s[k]<'0')||(s[k]>'?')) {
			return 0;
		}
		k++;
		}
	s[k]=0;
	k=0;
	while(s[k]!=0){
		ui64=ui64*16+(s[k]-'0');
		k++;
	}
	return ui64;
}
float  uart_getf		  (){ //betta
	int8_t sign=1;
	char s[6];
	int16_t i16=0;
	int8_t k=0;
	while(((s[k]=uart_getc())!='\r') && (s[k]!='.')&& (k < 5)){
		if ((s[0] =='-')&&(sign==1)){sign=-1;k--;}else
			if((s[k]<'0')||(s[k]>'9')) return 0;
		k++;
	}
	uint8_t flag;

	if (s[k]=='.') 	{flag='.';s[k]=0;}
	if (s[k]=='\r') {flag='\r';s[k]=0;}
	if (	k>5	  )	{flag='o';}
	k=0;
	int8_t j=0;
	while(s[j]!=0){
		i16=i16*10+(s[j]-'0');
		j++;
	}
	float resault=sign*i16;
	if (flag=='\r')	return resault;
	if (flag=='o' )	return resault;	
	if (flag== '.'){
		char ss[6];
		float uii16=0;	int8_t kk=0;
		while(((ss[kk]=uart_getc())!='\r') && (kk < 5)){
			if((ss[kk]<'0')||(ss[kk]>'9')) return resault;
			kk++;
			}
		ss[kk]=0;
		kk=0;
		while(ss[kk]!=0){
			uii16=uii16*10+(ss[kk]-'0');
			kk++;
			
		}
		uint16_t on=1;
		while (kk){
			 on*=10;
			kk--;
		}
		
		return resault+=uii16/on;
	}
	return	0;
} 
//#############################################################
#endif //UART_H

