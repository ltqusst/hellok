/*
 * monitor.c
 *
 *  Created on: Feb 2, 2015
 *      Author: tingqian
 */
#include "common.h"
#include "string.h"


//========================================================================
#define WHITE_SPACE 0x07
#define VIDEO_MEMORY 0xb8000

static char *videoMemory = (char*) VIDEO_MEMORY;

void clr_scr()
{
	int i;
	for(i=0;i < (80*25*2);i+=2)
	{
		videoMemory[i]=' ';
		videoMemory[i+1]=WHITE_SPACE;
	}
}

static void printxy(char *message, u32 x, u32 y)
{
	u32 i=0;
	i=(y*80*2)+x;
	while(*message!=0)
	{
		if(*message=='\n'){
			y++;
			i=(y*80*2);
		}
		else if(*message=='\r'){
			i=(y*80*2);
		}
		else{
			videoMemory[i++]=*message;
			videoMemory[i++]=WHITE_SPACE;
		}
		*message++;
	}
}

static char g_strtxt[1024];
int print_scr(u32 x, u32 y, char *fmt, ...)
{
	int len;
	va_list argptr;
	va_start(argptr, fmt);
	len = vspf(g_strtxt,sizeof(g_strtxt)-1, fmt, argptr);
	va_end(argptr);
	printxy(g_strtxt, x, y);
	return len;
}

