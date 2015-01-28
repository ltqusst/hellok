
ARCH := x86_64

all:hellok.elf
clean:
	rm -f *.o *.elf *.bin
	
hellok.elf: hello.o startup.o
	ld -T link.ld --oformat elf32-i386 -o hellok.elf startup.o hello.o

%.o : %.c 
	gcc -g -Wp,-MD,.$@.d -c -o $@ $<

%.o : %.s
	as  -g --gstabs -o $@ $<
