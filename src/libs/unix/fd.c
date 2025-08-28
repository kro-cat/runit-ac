#include <unistd.h>
#include <fcntl.h>
#include "fd.h"

int fd_copy(int to, int from)
{
	if (to == from)
		return 0;

	/*
	if (fcntl(from, F_GETFL, 0) == -1)
		return -1;

	close(to);

	if (fcntl(from, F_DUPFD, to) == -1)
		return -1;
	*/

	if (dup2(from, to) == -1)
		return -1;

	return 0;
}

int fd_move(int to, int from)
{
	if (to == from)
		return 0;

	if (fd_copy(to, from) == -1)
		return -1;

	close(from);
	return 0;
}
