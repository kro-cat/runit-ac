#include <signal.h>

#include <config.h>

#include "sig.h"


void (*sig_defaulthandler)(int) = SIG_DFL;
void (*sig_ignorehandler)(int) = SIG_IGN;

void sig_block(int sig)
{
#ifdef HASSIGPROCMASK
	sigset_t ss;
	sigemptyset(&ss);
	sigaddset(&ss,sig);
	sigprocmask(SIG_BLOCK, &ss, (sigset_t *) 0);
#else
	sigblock(1 << (sig - 1));
#endif
}

void sig_unblock(int sig)
{
#ifdef HASSIGPROCMASK
	sigset_t ss;
	sigemptyset(&ss);
	sigaddset(&ss,sig);
	sigprocmask(SIG_UNBLOCK, &ss, (sigset_t *) 0);
#else
	sigsetmask(sigsetmask(~0) & ~(1 << (sig - 1)));
#endif
}

void sig_blocknone(void)
{
#ifdef HASSIGPROCMASK
	sigset_t ss;
	sigemptyset(&ss);
	sigprocmask(SIG_SETMASK, &ss, (sigset_t *) 0);
#else
	sigsetmask(0);
#endif
}

void sig_catch(int sig, void (*f)(int))
{
#ifdef HASSIGACTION
	struct sigaction sa;
	sa.sa_handler = f;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(sig, &sa, (struct sigaction *) 0);
#else
	#warn "sigaction() is not available on your system. using the signal() function - this WILL NOT WORK on SysV !"
	signal(sig, f); /* won't work under System V, even nowadays---dorks */
#endif
}

void sig_pause(void)
{
#ifdef HASSIGPROCMASK
	sigset_t ss;
	sigemptyset(&ss);
	sigsuspend(&ss);
#else
	sigpause(0);
#endif
}
