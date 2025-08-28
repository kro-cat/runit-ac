#include "str.h"
#include "repeat.h"


#define OPS 8

unsigned int str_chr(register const char *s, int c)
{
	register char ch = c;
	register const char *t = s;

	for (;;) {
REPEAT(OPS,
		if ((!*t) ||(*t == ch))
			break;
		++t;
)
	}

	return t - s;
}

int str_diff(register const char *s, register const char *t)
{
	register char x;

	for (;;) {
REPEAT(OPS,
		x = *s;
		if ((x != *t) || (!x))
			break;
		++s;
		++t;
)
	}

	return ((int)(unsigned int)(unsigned char) x)
	- ((int)(unsigned int)(unsigned char) *t);
}

unsigned int str_len(const char *s)
{
	register const char *t;

	t = s;
	for (;;) {
REPEAT(OPS,
		if (!*t)
			return t - s;
		++t;
)
	}
}

int str_start(register const char *s, register const char *t)
{
	register char x;

	for (;;) {
REPEAT(OPS,
		x = *t++;

		if (!x)
			return 1;

		if (x != *s++)
			return 0;
)
	}
}
