CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
LD = arm-none-eabi-ld
CFLAGS = -O0 -c -g -mcpu=cortex-m4 -mthumb
INCFLAGS = -Iinc/CMSIS -Iinc
LDFLAGS = -T my_startup/K66F_linker_script.ld -Map=build/my/blinky.map
NXPFLAGS = -O0 -g -mcpu=cortex-m4 -mthumb -Iinc/CMSIS -Iinc -T nxp_startup/MK66FN2M0xxx18_flash.ld -Wl,--gc-sections,-Map=build/nxp/blinky.map,-lc,-lnosys -ffunction-sections -fdata-sections 

all: my nxp


my: build/my build/my/blinky.elf build/my/blinky.bin build/my/blinky.hex

build/my: build
	mkdir build/my

build/my/blinky.hex: build/my/blinky.elf
	$(OBJCOPY) -O ihex build/my/blinky.elf build/my/blinky.hex

build/my/blinky.bin: build/my/blinky.elf
	$(OBJCOPY) -O binary build/my/blinky.elf build/my/blinky.bin

build/my/blinky.elf: build/my/startup_K66F.o build/my/blinky.o build/my/system_MK66F18.o
	$(LD) $(LDFLAGS) $^ -o $@

build/my/system_MK66F18.o: src/system_MK66F18.c
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -o $@

build/my/startup_K66F.o: my_startup/startup_K66F.c
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -o $@

build/my/blinky.o: src/blinky.c
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -o $@


nxp: build/nxp build/nxp/blinky.elf build/nxp/blinky.bin

build/nxp: build
	mkdir build/nxp

build/nxp/blinky.bin: build/nxp/blinky.elf
	$(OBJCOPY) -O binary $^ $@

build/nxp/blinky.elf: nxp_startup/startup_MK66F18.S src/blinky.c src/system_MK66F18.c
	$(CC) $(NXPFLAGS) $^ -o $@


build:
	mkdir build

clean:
	rm -rf build
