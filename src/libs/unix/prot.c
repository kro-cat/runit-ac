#include <unistd.h>

#include <config.h>

#include "prot.h"


int setgroups_short(int size, unsigned *gid)
{
#ifdef HASPOSIXSETGROUPS
	short x[2];

	/* catch errors */
	x[0] = *gid;
	x[1] = 73;

	return setgroups(size, x);
#else
	return setgroups(size, gid);
#endif
}

int prot_gid(unsigned gid)
{
	if (setgroups_short(1, &gid) == -1)
		return -1;

	/* _should_ be redundant, but on some systems it isn't */
	return setgid(gid);
}

int prot_uid(int uid)
{
	return setuid(uid);
}
