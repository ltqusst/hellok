#include "common.h"
#include "stdarg.h"
#include "string.h"

char * _strcpy(char * dst, const char *src)
{
	while(*src) *dst++ = *src++;
	*dst = 0;
	return dst;
}
char* _int2string(int v, char cfmt, char * pos)
{
	char tmp[11];
	u32 u32v = v<0?(-v):v;
	int p = 11, d;

	if(u32v == 0) {
		*pos++ = '0';
		*pos = '\0';
		return pos;
	}

	if(cfmt == 'x'){
		while(u32v > 0){
			p--;
			d = u32v & 0xF;
			u32v >>= 4;
			tmp[p] = d<10?('0'+d):('A'+d-10);
		}
	}
	if(cfmt == 'd'){
		while(u32v > 0){
			p--;
			d = u32v % 10;
			u32v = u32v/10;
			tmp[p] = '0' + d;
		}
	}

	if(v<0) {
		p--;
		tmp[p] = '-';
	}

	for(;p<11;p++) *pos++ = tmp[p];
	*pos = '\0';
	return pos;
}

int vspf(char * buffer, int bufsize, char *fmt, va_list argptr)
{
	char * buf = buffer;
	char * bufend = buffer + bufsize;
	int cnt;
	int data;
	while((*fmt) && (buf < bufend))
	{
		if(*fmt == '%')
		{
			fmt++;
			switch(*fmt)
			{
			case 'd':
			case 'x':
				data = va_arg(argptr, int);
				buf = _int2string(data, *fmt, buf);
				fmt ++;
				break;
			case's':
				buf = _strcpy(buf, va_arg(argptr, char *));
				fmt ++;
				break;
			default:
				*buf++ = fmt[-1];
				*buf++ = fmt[0];
				fmt++;
				break;
			}
			continue;
		}
		else if(*fmt == 0) break;
		else *buf++ = *fmt++;
	}
	*buf = 0;
	cnt = buf - buffer;

	return(cnt);
}


