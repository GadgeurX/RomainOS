#ifndef		LIBC_H_
#define		LIBC_H_

#include	"types.h"

void* memcpy(char* dstptr, char* srcptr, u32 size);
u32 strlen(const char* str);

#endif
