/*
 * string.h
 *
 *  Created on: Feb 2, 2015
 *      Author: tingqian
 */

#ifndef STRING_H_
#define STRING_H_

#include "stdarg.h"

char * _strcpy(char * dst, const char *src);
char* _int2string(int v, char cfmt, int zero_lead, int digit_cnt, char * pos);
int vspf(char * buffer, int bufsize, char *fmt, va_list argptr);

#endif /* STRING_H_ */
