
ARCH := x86_64

all:hello.elf
clean:
	rm -f *.o *.elf
	
hello.elf: hello.o startup.o
	ld -T link.ld --oformat elf32-i386 -o kernel.bin startup.o hello.o

%.o : %.c 
	gcc -Wp,-MD,.$@.d -c -o $@ $<

%.o : %.s
	as  -o $@ $<
