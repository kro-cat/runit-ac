#include "byte.h"
#include "repeat.h"


unsigned int byte_chr(const char *const s, register unsigned int n,
		      register const int c)
{
	register const char *t = s;

	for (;;) {
REPEAT8(
		if (!n || (*t == (const char)c))
			break;
		++t;
		--n;
)
	}

	return t - s;
}

unsigned int byte_rchr(const char *const s, register unsigned int n,
		       register const int c)
{
	register const char *t = s;
	register const char *u = 0;

	for (;;) {
REPEAT8(
		if (!n)
			break;
		if (*t == (const char)c)
			u = t;
		++t;
		--n;
)
	}

	if (!u)
		u = t;

	return u - s;
}

void byte_copy(register char *to, register unsigned int n,
	       register const char *from)
{
	for (;;) {
REPEAT8(
		if (!n)
			break;
		*to++ = *from++;
		--n;
)
	}
}

void byte_copyr(register char *to, register unsigned int n,
		register const char *from)
{
	to += n;
	from += n;

	for (;;) {
REPEAT8(
		if (!n)
			break;
		*--to = *--from;
		--n;
)
	}
}

int byte_diff(register const char *s, register unsigned int n,
	      register const char *t)
{
	for (;;) {
REPEAT8(
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


