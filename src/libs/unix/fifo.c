#include <sys/types.h>
#include <sys/stat.h>

#include <config.h>

#include "fifo.h"


int fifo_make(const char *fn, int mode) {
#ifdef HASMKFIFO
	return mkfifo(fn, mode);
#else
	return mknod(fn, S_IFIFO | mode, 0);
#endif
}
