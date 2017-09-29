#include	"libc.h"

void *memcpy(char *dst, char *src, u32 n)
{
	char *p = dst;
	while (n--)
		*dst++ = *src++;
	return p;
}
