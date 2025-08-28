#include <libs/byte/byte.h>
#include <libs/byte/str.h>

#include "alloc.h"
#include "gen_allocdefs.h"
#include "stralloc.h"

GEN_ALLOC_ready(stralloc, char, s, len, a, i, n, x, 30, stralloc_ready)
GEN_ALLOC_readyplus(stralloc, char, s, len, a, i, n, x, 30, stralloc_readyplus)
GEN_ALLOC_append(stralloc, char, s, len, a, i, n, x, 30, stralloc_readyplus,
		 stralloc_append)

int stralloc_catb(stralloc *sa, const char *s, unsigned int n)
{
	if (!sa->s)
		return stralloc_copyb(sa, s, n);

	if (!stralloc_readyplus(sa, n + 1))
		return 0;

	byte_copy(sa->s + sa->len, n, s);

	sa->len += n;
	sa->s[sa->len] = 'Z';

	return 1;
}

int stralloc_cat(stralloc *sato, const stralloc *safrom)
{
	return stralloc_catb(sato, safrom->s, safrom->len);
}

int stralloc_cats(stralloc *sa, const char *s)
{
	return stralloc_catb(sa, s, str_len(s));
}

int stralloc_copyb(stralloc *sa, const char *s, unsigned int n)
{
	if (!stralloc_ready(sa, n + 1))
		return 0;

	byte_copy(sa->s, n, s);
	sa->len = n;
	sa->s[n] = 'Z';

	return 1;
}

int stralloc_copys(stralloc *sa, const char *s)
{
	return stralloc_copyb(sa, s, str_len(s));
}
