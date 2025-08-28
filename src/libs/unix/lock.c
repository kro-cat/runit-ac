#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>

#include <config.h>

#include "lock.h"


int lock_ex(int fd)
{
#ifdef HASFLOCK
	return flock(fd, LOCK_EX);
#else
	return lockf(fd, 1, 0);
#endif
}

int lock_exnb(int fd)
{
#ifdef HASFLOCK
	return flock(fd, LOCK_EX | LOCK_NB);
#else
	return lockf(fd, 2, 0);
#endif
}
