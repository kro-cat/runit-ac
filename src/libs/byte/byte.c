#include "byte.h"
#include "repeat.h"


#define OPS 8

unsigned int byte_chr(char *s, register unsigned int n, int c)
{
	register char ch = c;
	register char *t = s;

	for (;;) {
REPEAT(OPS,
		if (!n || (*t == ch))
			break;
		++t;
		--n;
)
	}

	return t - s;
}

unsigned int byte_rchr(char *s, register unsigned int n, int c)
{
	register char ch = c;
	register char *t = s;
	register char *u = 0;

	for (;;) {
REPEAT(OPS,
		if (!n)
			break;
		if (*t == ch)
			u = t;
		++t;
		--n;
)
	}

	if (!u) u = t;
	return u - s;
}

void byte_copy(register char *to, register unsigned int n, register char *from)
{
	for (;;) {
REPEAT(OPS,
		if (!n)
			break;
		*to++ = *from++;
		--n;
)
	}
}

void byte_copyr(register char *to, register unsigned int n, register char *from)
{
	to += n;
	from += n;

	for (;;) {
REPEAT(OPS,
		if (!n)
			break;
		*--to = *--from;
		--n;
)
	}
}

int byte_diff(register char *s, register unsigned int n, register char *t)
{
	for (;;) {
REPEAT(OPS,
		if (!n)
			return 0;
		if (*s != *t)
			break;
		++s;
		++t;
		--n;
)
	}

	return ((int)(unsigned int)(unsigned char) *s)
	- ((int)(unsigned int)(unsigned char) *t);
}


