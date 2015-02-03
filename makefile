
ARCH := x86_64
TARGET = hellok.elf

OBJS += hello.o startup.o 
OBJS += string.o monitor.o 

VPATH += ./ ./utils 
# INC_DIR += utils

CFLAGS += -nostdlib -nostartfiles
CFLAGS += $(patsubst %,-I%,$(subst :, ,$(VPATH)))

all:$(TARGET)
clean:
	rm -f *.o *.elf *.bin
	
$(TARGET): $(OBJS)
	@echo VPATH=$(VPATH)
	ld -T link.ld --oformat elf32-i386 -o $@ $^

%.o : %.c 
	gcc -g $(CFLAGS) -Wp,-MD,.$@.d -c -o $@ $<

%.o : %.s
	as -g -o $@ $<
