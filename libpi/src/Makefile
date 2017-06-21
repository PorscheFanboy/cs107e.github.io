ARMGNU ?= arm-none-eabi

CC = $(ARMGNU)-gcc
AS = $(ARMGNU)-as
AR = $(ARMGNU)-ar
LD = $(ARMGNU)-ld
OBJDUMP = $(ARMGNU)-objdump

#ARCHFLAGS = -mfloat-abi=hard -march=armv6
CPPFLAGS = -I../include
ARCHFLAGS = -march=armv6
CFLAGS = -std=c99 -Wall -g -Og -ffreestanding 
CFLAGS += -mapcs-frame -fno-omit-frame-pointer
CFLAGS += -ffunction-sections -fdata-sections
# don't embed full path in .o so as to make build deterministc
CFLAGS += -gno-record-gcc-switches -fdebug-prefix-map=`pwd`=.
# keep clang happy
#CFLAGS += -fno-short-enums
CFLAGS += $(ARCHFLAGS) $(CPPFLAGS)
ASFLAGS = $(ARCHFLAGS) $(CPPFLAGS)

NOTUSED_SRCS = cstart.c interrupt_handlers.c
SRCS = abort.c system.c mmu.c interrupts.c reboot.c printf.c uart.c timer.c armtimer.c gpio.c gpioextra.c gpioevent.c debounce.c led.c pwm.c tone.c mailbox.c property.c fb.c font.c gl.c keyboard-async.c pmu.c rand.c malloc.c circular.c console.c strtol.c backtrace.c mouse.c paint.c shell.c spi.c i2c.c sd.c fat.c fs.c keyboard-emulator.c ps2.c
ASRCS = register.s memory.s vectors.s
OBJS = ${SRCS:.c=.o} ${ASRCS:.s=.o}

all : libpi.a 

clean :
	rm -f *.o
	rm -f *.d
	rm -f *.a
	rm -f *~

install: libpi.a keyboard-sync.o
	cp libpi.a ../lib
	cp *.o ../modules

# use archive -D flag to timestamp=zero, binary file will be deterministic
libpi.a: $(OBJS) 
	$(AR) rD $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -DLIBPI_INTERNAL -c $< -o $@
	$(CC) $(CFLAGS) -c $< -o ../modules/$@
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) -c $< > $*.d

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.list: %.o
	$(OBJDUMP) -d --no-show-raw-insn $< > $@

# include dependency rules
#  "-" supresses errors if the .d files are not present
-include $(SRCS:.c=.d)
