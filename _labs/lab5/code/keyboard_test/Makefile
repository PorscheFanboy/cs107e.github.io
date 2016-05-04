# Set variables to correct tools
ARMGNU = arm-none-eabi
CC = $(ARMGNU)-gcc
AS = $(ARMGNU)-as
NM = $(ARMGNU)-nm
AR = $(ARMGNU)-ar
OBJCOPY = $(ARMGNU)-objcopy
OBJDUMP = $(ARMGNU)-objdump

# Configure compile options via CFLAGS
#  -Wall     		give verbose compiler warnings
#  -Og       		apply moderate optimization, retain structure for debugging
#  -std=gnu99  		use the C99 standard language definition with GNU extenions
#  -ffreestanding	do not assume presence of standard library (non-hosted)
CFLAGS = -Wall -Og -g -std=gnu99 -ffreestanding -I../../../../libpi/include

# Configure linker options via LDFLAGS, LDLIBS
#  -nostdlib   	do not link standard system startup nor default libraries
#  -T memmap    use our linker map
LDFLAGS = -nostdlib -T memmap
LDLIBS = -L../../../../libpi/lib -L../../../../lib -lpi -lgcc

# Set name of the executable, built from single source file 'name.'
# Edit here to change executable name or add/remove/change source files
NAME = main
SOURCES = $(NAME).c 
OBJECTS = $(SOURCES:.c=.o) start.o interrupt_handlers.o cstart.o

# The first target listed in the makefile is the default product built when
# make is invoked with no argument
all: $(NAME).bin 

# Link object files into elf executable, use custom start.o in place of default
$(NAME).elf: $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

# The install target uploads freshly made binary image to rpi bootloader
install: $(NAME).bin
	rpi-install.py $<

# This pattern rule creates binary 'name.bin' by extracting raw instructions
# from executable 'name.elf'
%.bin: %.elf 
	$(OBJCOPY) $< -O binary $@

# This pattern rule produces 'name.list' assembly listing by disassembling 'name.o'
%.list: %.o
	$(OBJDUMP) -d $< > $@

# These 2 pattern rules not truly necessary, just make explicit what was implicit...
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

# The clean target removes previous build products, will force build a-new on next make
clean:
	rm -f *.o *.bin *.elf *.list *.text *.d *~
	rm -f lib/libpi.a 
	rm -f libsyms.txt appsyms.txt warning.txt common.txt

# Targets that aren't filename of build product should be declared "phony"
.PHONY: all clean

# Note this Makefile does not build a custom libpi with the rules below;
# it just uses the full reference libpi, as this is a test app.
LIBPI_INCLUDED = system.o register.o mailbox.o gpio.o gpioextra.o 
LIBPI_MODULES  = $(patsubst %.o,%,$(LIBPI_INCLUDED))
LIBPI_INCLUDED_WITH_PATH = $(patsubst %.o,lib/%.o,$(LIBPI_INCLUDED))

libpi: 
	@echo "Building libpi"
	@echo "   Including modules: $(LIBPI_MODULES)"
	$(AR) r lib/libpi.a $(LIBPI_INCLUDED_WITH_PATH)
	@echo "Checking that your application and libpi don't conflict."
	@$(NM) lib/libpi.a | grep " T " | sed "s/[0-9a-f]* T \([a-z_]*\)/\1/g" | sort > libsyms.txt
	@$(NM) $(OBJECTS) | grep " T " | sed "s/[0-9a-f]* T \([a-z_]*\)/\1/g"  | sort > appsyms.txt
	@echo "WARNING: Your libpi and application both define the following symbols." > warning.txt
	@echo "This means you are including reference implementations of code" >> warning.txt
	@echo "that you have implemented, so you might think your code works when" >> warning.txt
	@echo "it doesn't, or this might break your code. Be sure that, for each .o" >> warning.txt
	@echo "file, you either include it in libpi or in your application but not both:" >> warning.txt
	@comm -1 -2 libsyms.txt appsyms.txt > common.txt
	@if test -s common.txt; then tput bold; tput setaf 1;cat warning.txt common.txt;tput sgr0; fi
	@rm libsyms.txt appsyms.txt warning.txt common.txt

#LIBPI_INCLUDED += gl.o
