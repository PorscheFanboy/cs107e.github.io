ARMGNU ?= arm-none-eabi

CC = $(ARMGNU)-gcc
AS = $(ARMGNU)-as
AR = $(ARMGNU)-ar
LD = $(ARMGNU)-ld
OBJDUMP = $(ARMGNU)-objdump

#ARCHFLAGS = -mfloat-abi=hard -march=armv6
CPPFLAGS = -I../include -I../../libpi/include
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

NOTUSED_SRCS = 
SRCS = mmu.c debounce.c tone.c property.c pmu.c rand.c paint.c spi.c i2c.c sd.c fat.c fs.c 
ASRCS = 
OBJS = ${SRCS:.c=.o} ${ASRCS:.s=.o}

all : libpiextra.a 

clean :
	rm -f *.o
	rm -f *.d
	rm -f *.a
	rm -f *~

install: libpiextra.a keyboard-sync.o
	cp libpiextra.a ../lib

# use archive -D flag to timestamp=zero, binary file will be deterministic
libpiextra.a: $(OBJS) 
	$(AR) rD $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -DLIBPI_INTERNAL -c $< -o $@
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) -c $< > $*.d

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.list: %.o
	$(OBJDUMP) -d --no-show-raw-insn $< > $@

# include dependency rules
#  "-" supresses errors if the .d files are not present
-include $(SRCS:.c=.d)
