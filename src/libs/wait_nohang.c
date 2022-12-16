/* Public domain. */

#include <sys/types.h>
#include <sys/wait.h>
#include <config.h>

int wait_nohang(wstat) int *wstat;
{
#ifdef HASWAITPID
  return waitpid(-1,wstat,WNOHANG);
#else
#warn "waitpid() is not available on your system. using the obsolete wait3() function."
  return wait3(wstat,WNOHANG,(struct rusage *) 0);
#endif
}
