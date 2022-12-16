/* Public domain. */

#include <signal.h>
#include "sig.h"
#include <config.h>
//#include "hassgact.h"

void sig_catch(int sig,void (*f)())
{
#ifdef HASSIGACTION
  struct sigaction sa;
  sa.sa_handler = f;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(sig,&sa,(struct sigaction *) 0);
#else
#warn "sigaction() is not available on your system. using the signal() function - this WILL NOT WORK on SysV !"
  signal(sig,f); /* won't work under System V, even nowadays---dorks */
#endif
}
