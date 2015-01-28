ARCH := x86_64
TARGET = hellok.elf

 
all:$(TARGET)
clean:
	rm -f *.o *.elf *.bin
	
$(TARGET): hello.o startup.o
	ld -T link.ld --oformat elf32-i386 -o $@ $^

%.o : %.c 
	gcc -g -nostdlib -nostartfiles  -Wp,-MD,.$@.d -c -o $@ $<

%.o : %.s
	as -g -o $@ $<
