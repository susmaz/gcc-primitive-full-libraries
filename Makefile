CForce 		= -funsigned-char -funsigned-bitfields  -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -fno-merge-constants 
CWarnings	= -Wall -Wextra -Wno-write-strings
CFlag		= -mmcu=atmega328 -DF_CPU=16000000UL -DNDEBUG -std=gnu11 -Os $(CWarnings)  $(CForce) 
LinkerOptions	= -Wl,-Map=bin/main.map -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections
all:
	avr-gcc --version
	rm -rf bin
	mkdir bin
	avr-gcc		-c main.c  -o bin/main.o  $(CFlag)
	avr-gcc 	bin/main.o -o bin/main.elf -mmcu=atmega328	$(LinkerOptions)	
	avr-objdump -h -S 	bin/main.elf > 	bin/main.lss
	avr-objcopy -O ihex	bin/main.elf 	bin/main.hex
	avr-size  	-C 	--mcu=atmega328		bin/main.elf
clean: 
	rm -rf bin
program:burn
	avrdude  -p m328p -c stk500v2 -P avrdoper -U flash:w:bin/main.hex:a 
burn: 
	avrdude -q -q -p m328p -c stk500v2 -P avrdoper -U lfuse:w:0xFF:m 	-U hfuse:w:0xD9:m 	-U efuse:w:0xff:m 
	