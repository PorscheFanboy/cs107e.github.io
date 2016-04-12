#
# A simple makefile for building program composed of C/asm source files.
# Builds for ARM target using cross-development toolchain. 
#

# Configure compile options via CFLAGS
#  -g        	compile with debug information
#  -Wall     	give verbose compiler warnings
#  -Og       	apply moderate optimization, retain structure for debugging
#  -std=c99  	use the C99 standard language definition
#  -ffreestanding	do not assume presence of standard library (non-hosted)
CFLAGS = -g -Wall -Og -std=c99 -ffreestanding

# Configure assembler options via ASFLAGS
#  -x assembler-with-cpp	allow use of C preprocessor in assembly
ASFLAGS = -x assembler-with-cpp

# Configure linker options via LDFLAGS, LDLIBS
#  -nostdlib   	do not link standard system startup nor default libraries
#  -T memmap    use our linker map
LDFLAGS = -nostdlib -T memmap

# The first target listed in the makefile is the default product built when
# make is invoked with no argument. By default, this makefile builds two 
# executables and dumps the generated assembly into text files for review
all : codegen.bin codegen.list ptrs.bin ptrs.list

# This pattern rule creates binary 'name.bin' by extracting raw instructions 
# from executable 'name.elf'
%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

# This pattern rule creates elf executable 'name.elf' by linking 'name.o' 
# and custom start.o (used in place of default start files)
%.elf: start.o %.o
	arm-none-eabi-gcc $(LDFLAGS) $^ -o $@

# These 2 pattern rules not truly necessary, just make explicit what was implicit...
%.o: %.c
	arm-none-eabi-gcc $(CFLAGS)  -c $< -o $@
%.o: %.s
	arm-none-eabi-gcc $(ASFLAGS) -c $< -o $@

# This pattern rule produces 'name.list' assembly listing by disassembling 'name.o'
# This is an optional product you can make to review the assembly
%.list: %.o
	arm-none-eabi-objdump -d $< > $@

# The install target uploads freshly made binary image to rpi bootloader
install: codegen.bin
	rpi-install.py $^

# The clean target removes previous build products, will force build a-new on next make
clean:
	rm -f *.o *.bin *.elf *.list
