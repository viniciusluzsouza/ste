PRG = main
PORT = /dev/ttyUSB0
TARGET_HW = atmega2560
CC = avr-g++
OBJCOPY = avr-objcopy
DUMP = avr-objdump
PRGFLASH = avrdude
DEFS =
LIBS = PCInt.cpp UART.cpp
OPTIMIZE = -O2
STD = -std=c++11
CFLAGS = -g -Wall $(STD) $(OPTIMIZE) -mmcu=$(TARGET_HW) $(DEFS)

all: $(PRG).hex debug clean

GPIO.o:
	$(CC) $(CFLAGS) -c GPIO.cpp

$(PRG).o:
	$(CC) $(CFLAGS) -c $(PRG).cpp

$(PRG).elf: $(PRG).o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(PRG).hex: $(PRG).elf
	$(OBJCOPY) -j .text -j .data -O ihex $(PRG).elf $(PRG).hex

debug:
	$(DUMP) -h -S $(PRG).elf > $(PRG).lst
	
flash:
	$(PRGFLASH) -p $(TARGET_HW) -c wiring -P $(PORT) -D -U flash:w:$(PRG).hex:i
	
clean:
	rm *.o *.elf

clear:
	rm *.o *.elf *.hex *.lst

