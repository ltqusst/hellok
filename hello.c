#define WHITE_SPACE 0x07
#define VIDEO_MEMORY 0xb8000

char *videoMemory = (char*) VIDEO_MEMORY;

void clrscr()
{
	int i;
	for(i=0;i < (80*25*2);i+=2)
	{
		videoMemory[i]=' ';
		videoMemory[i+1]=WHITE_SPACE;
	}
}

void printxy(char *message, unsigned int x, unsigned int y)
{
	unsigned int i=0;
	i=(y*80*2)+x;
	while(*message!=0)
	{
		if(*message=='\n')
		{
			y++;
			i=(y*80*2);
		}else{
			videoMemory[i++]=*message;
			videoMemory[i++]=WHITE_SPACE;
		}
		*message++;
	}
}
extern unsigned int bss;
extern unsigned int bss_end;
void kernel_main()
{
	int i;
	char data[5]={0};

	for(i=0;i<bss_end-bss;i++) ((char*)bss)[i] = 0;

	clrscr();
	for(i=0;;i++)
	{
		data[3] = '0'+((int)(&bss) & 0xFF);
		data[2] = '0'+((i>>8) & 0xFF);
		data[1] = '0'+((i>>16) & 0xFF);
		data[0] = '0'+((i>>24) & 0xFF);
		data[4] = 0;
		printxy(data, 0, 2);
		printxy("Hello World", 0, 0);
	}
}

