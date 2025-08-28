#include "fmt.h"

unsigned int fmt_uint0(char *s, unsigned int u, unsigned int n)
{
	unsigned int len = fmt_uint(FMT_LEN, u);

	while (len < n) {
		if (s)
			*s++ = '0';

		++len;
	}

	if (s)
		fmt_uint(s, u);

	return len;
}

unsigned int fmt_uint(register char *s, register unsigned int u)
{
	return fmt_ulong(s, u);
}

unsigned int fmt_ulong(register char *s, register unsigned long u)
{
	register unsigned int len = 1;
	register unsigned long q = u;

	while (q > 9) {
		++len;
		q /= 10;
	}

	if (s) {
		s += len;
		do {
			*--s = '0' + (u % 10);
			u /= 10;
		} while(u); /* handles u == 0 */
	}

	return len;
}
