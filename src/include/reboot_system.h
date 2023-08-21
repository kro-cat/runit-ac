#include <config.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/reboot.h>

int reboot_system(int what) {
#ifdef UNGRACEFUL_DEATH
	_exit(what);
#else
# ifdef NONSTDREBOOT
	return(reboot(what, (char *)0));
# else
	return(reboot(what));
# endif
#endif
}

