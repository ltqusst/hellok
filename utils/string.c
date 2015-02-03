#include "common.h"
#include "stdarg.h"
#include "string.h"

char * _strcpy(char * dst, const char *src)
{
	while(*src) *dst++ = *src++;
	*dst = 0;
	return dst;
}
char* _int2string(int v, char cfmt, int zero_lead, int digit_cnt, char * pos)
{
	char tmp[32];
	u32 u32v = v<0?(-v):v;
	int p = 32, d;

	if(u32v == 0) {
		*pos++ = '0';
		*pos = '\0';
		digit_cnt--;
	}
	else
	if(cfmt == 'x' || cfmt == 'X'){
		while(u32v > 0){
			p--;
			d = u32v & 0xF;
			u32v >>= 4;
			tmp[p] = d<10?('0'+d):((cfmt=='x'?'a':'A')+d-10);
			digit_cnt --;
		}
	}
	else
	if(cfmt == 'd'){
		while(u32v > 0){
			p--;
			d = u32v % 10;
			u32v = u32v/10;
			tmp[p] = '0' + d;
			digit_cnt--;
		}
	}

	if(v<0) {
		p--;
		tmp[p] = '-';
	}
	while(digit_cnt > 0 && p>0){
		p--;
		tmp[p] = zero_lead?'0':' ';
		digit_cnt--;
	}

	for(;p<32;p++) *pos++ = tmp[p];
	*pos = '\0';
	return pos;
}

int vspf(char * buffer, int bufsize, char *fmt, va_list argptr)
{
	char * buf = buffer;
	char * bufend = buffer + bufsize;
	int cnt;
	int data;
	int zero_lead;
	int digit_cnt;
	while((*fmt) && (buf < bufend))
	{
		if(*fmt == '%')
		{
			fmt++;
			zero_lead = 0;
			digit_cnt = 0;
			if(*fmt == '0') {zero_lead = 1;fmt++;}
			while(*fmt >= '0' && *fmt <= '9') {digit_cnt = digit_cnt*10 + (*fmt)-'0'; fmt++;}
			switch(*fmt)
			{
			case 'd':
			case 'x':
			case 'X':
				data = va_arg(argptr, int);
				buf = _int2string(data, *fmt, zero_lead, digit_cnt, buf);
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


