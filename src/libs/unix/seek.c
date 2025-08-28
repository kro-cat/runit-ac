#include <unistd.h>
#include <sys/types.h>

#include "seek.h"


int seek_set(int fd, seek_pos pos)
{
	if (lseek(fd, (off_t) pos, 0) == -1)
		return -1;

	return 0;
}
