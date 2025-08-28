#include <sys/types.h>
#include <sys/wait.h>

#include <config.h>

int wait_nohang(int *wstat)
{
	return waitpid(-1, wstat, WNOHANG);
}

int wait_pid(int *wstat, int pid)
{
	int r;

	do {
		r = waitpid(pid, wstat, 0);
	} while ((r == -1) && (errno == error_intr));

	return r;
}
