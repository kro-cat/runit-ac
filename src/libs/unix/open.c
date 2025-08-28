#include <sys/types.h>
#include <fcntl.h>

#include "open.h"


int open_append(const char *fn)
{
	return open(fn, O_WRONLY | O_NDELAY | O_APPEND | O_CREAT, 0600);
}

int open_read(const char *fn)
{
	return open(fn, O_RDONLY | O_NDELAY);
}

int open_trunc(const char *fn)
{
	return open(fn, O_WRONLY | O_NDELAY | O_TRUNC | O_CREAT,0644);
}

int open_write(const char *fn)
{
	return open(fn, O_WRONLY | O_NDELAY);
}
