#include <config.h>

#include <sys/types.h>
#include <sys/reboot.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <runit.h>
#include <sig.h>
#include <strerr.h>
#include <error.h>
#include <iopause.h>
#include <coe.h>
#include <ndelay.h>
#include <wait.h>
#include <open.h>
#include <reboot_system.h>

/* #define DEBUG */

#define INFO "- runit: "
#define WARNING "- runit: warning: "
#define FATAL "- runit: fatal: "

int selfpipe[2];

struct childinfo *stage;



/*****************************************************************************
 * Helpers
 *****************************************************************************/

void reget_stderr()
{
	int fd;

	/* reget stderr */
	if ((fd = open_write("/dev/console")) != -1) {
		dup2(fd, 2);
		if (fd > 2)
			close(fd);
	}
}

void log_stage_exit(const char * stage_path, int stage_wstat)
{
	reget_stderr();

	if (wait_exitcode(stage_wstat) != 0) {
		if (wait_crashed(stage_wstat)) {
			strerr_warn3(WARNING, "stage crashed: ", stage_path, 0);
		} else {
			strerr_warn3(WARNING, "stage failed: ", stage_path, 0);
		}
	}

	strerr_warn3(INFO, "leave stage: ", stage_path, 0);
}



/*****************************************************************************
 * Process Execution
 *****************************************************************************/

char * const *global_envp;

pid_t fork_exec(const char *path, void (*child_init)())
{
	pid_t pid;
	const char * args[2] = {0};

	while ((pid = fork()) == -1) {
		strerr_warn4(FATAL, "unable to fork for \"", path,
				"\" pausing: ", &strerr_sys);
		sleep(5);
	}

	if (!pid) {
		/* child */
		setsid();

		sig_uncatch(sig_child);
		sig_uncatch(sig_int);
		sig_ignore(sig_cont);

		sig_unblock(sig_alarm);
		sig_unblock(sig_cont);
		sig_unblock(sig_hangup);
		sig_unblock(sig_int);
		sig_unblock(sig_pipe);
		sig_unblock(sig_term);

		if (child_init)
			child_init();

		args[0] = path;
		execve(path, (char * const *) args, global_envp);
		strerr_die4sys(0, FATAL, "unable to start child: ", path, ": ");
	}

	/* parent returns */
	return pid;
}



/*****************************************************************************
 * Child control
 *****************************************************************************/

struct childinfo {
	pid_t pid;
	int wstat;
};

#define MAX_CHILDREN 10

size_t num_children = 0;
struct childinfo children[MAX_CHILDREN] = {0};

struct childinfo *add_child(pid_t pid)
{
	size_t i, c;

	if (num_children == MAX_CHILDREN) {
		strerr_warn2(FATAL, "no space for new children!", 0);
		return NULL;
	}

	for (i = 0, c = 0; (i < MAX_CHILDREN) && (c < num_children); i++) {
		if (children[i].pid == 0)
			break;
		c++;
	}

	if (i == MAX_CHILDREN) {
#ifdef DEBUG
		strerr_warn2(WARNING, "no space for new children!", 0);
#endif
		return NULL;
	}

	children[i].pid = pid;
	children[i].wstat = 0;

#ifdef DEBUG
	strerr_warn2(INFO, "child added to watchlist", 0);
#endif

	return &(children[i]);
}

struct childinfo *find_child(pid_t pid)
{
	size_t i, c;

	for (i = 0, c = 0; (i < MAX_CHILDREN) && (c < num_children); i++) {
		if (children[i].pid == pid)
			break;
		c++;
	}

	if (i == MAX_CHILDREN) {
#ifdef DEBUG
		strerr_warn2(WARNING, "child not found in watchlist", 0);
#endif
		return NULL;
	}

	return &(children[i]);
}

struct childinfo *del_child(pid_t pid)
{
	struct childinfo *child;

	if ((child = find_child(pid))) {
		child->pid = 0;
		num_children--;
#ifdef DEBUG
		strerr_warn2(INFO, "child removed from watchlist", 0);
#endif
	}

	return child;
}

#define child_stopped(X) \
	((((struct childinfo *)X)->pid == 0) || \
	 wait_stopped(((struct childinfo *)X)->wstat))



/*****************************************************************************
 * Signal Handlers
 *****************************************************************************/

void child_wait()
{
	/* handle child signals */
	pid_t pid;
	int wstat;
	struct childinfo *child;

	do {
		if ((pid = wait_nohang(&wstat)) > 0) {
			if (wait_exited(wstat)) {
				if ((child = del_child(pid))) {
					reget_stderr();
					child->wstat = wstat;
				}
			} else if ((child = find_child(pid))) {
				reget_stderr();
				child->wstat = wstat;
			}
		} else if ((pid == -1) && (errno != ECHILD)) {
			/*
			stage_wstat = 0;
			stage_pid = 0;
			strerr_warn3(0, WARNING, "child handler: wait_pid: ", &strerr_sys);
			*/
			strerr_warn2(FATAL, "wait_nohang: ", &strerr_sys);
		}
	} while (pid > 0);
}

void stage2_only()
{
	strerr_warn2(WARNING, "signals only work in stage 2.", 0);
}

void stopit()
{
	int i;
	struct stat s;

	if ((stat(STOPIT, &s) != -1) && (s.st_mode & S_IXUSR)) {
		/* unlink(STOPIT); */
		chmod(STOPIT, 0);

		/* kill stage 2 */
		if (child_stopped(stage))
			return;

#ifdef DEBUG
		strerr_warn2(WARNING, "sending sigterm...", 0);
#endif
		kill(stage->pid, sig_term);

		reget_stderr();

		for (i = 0; i < 5; i++) {
			if (child_stopped(stage)) {
#ifdef DEBUG
				strerr_warn2(WARNING, "stage 2 terminated.", 0);
#endif
				break;
			}
#ifdef DEBUG
			strerr_warn2(WARNING, "waiting...", 0);
#endif
			sleep(1);
		}

		if (!child_stopped(stage)) {
			/* still there */
			strerr_warn2(WARNING,
					"stage 2 not terminated, sending sigkill...", 0);
			kill(stage->pid, 9);
			if (wait_pid(&(stage->wstat), stage->pid) == -1)
				strerr_warn2(WARNING, "wait_pid: ", &strerr_sys);
		}
	}
}

void ctrlaltdel()
{
	struct stat s;
	struct childinfo *child;

	if ((stat(CTRLALTDEL, &s) != -1) && (s.st_mode & S_IXUSR)) {
		strerr_warn2(INFO, "ctrl-alt-del request...", 0);

		strerr_warn3(INFO, "enter stage: ", CTRLALTDEL, 0);

		child = add_child(fork_exec(CTRLALTDEL, 0));

		while (!child_stopped(child)) {
#ifdef DEBUG
			strerr_warn2(WARNING, "waiting...", 0);
#endif
			sleep(1);
		}

		log_stage_exit(CTRLALTDEL, child->wstat);

		stopit();
	}
}

void powerfail()
{
	struct stat s;
	struct childinfo *child;

	if ((stat(POWERFAIL, &s) != -1) && (s.st_mode & S_IXUSR)) {
		strerr_warn2(INFO, "power failure! ", 0);

		strerr_warn3(INFO, "enter stage: ", POWERFAIL, 0);

		child = add_child(fork_exec(POWERFAIL, 0));

		while (!child_stopped(child)) {
#ifdef DEBUG
			strerr_warn2(WARNING, "waiting...", 0);
#endif
			sleep(1);
		}

		log_stage_exit(POWERFAIL, child->wstat);

		stopit();
	}
}



/*****************************************************************************
 * Staging
 *****************************************************************************/

void stage1_init()
{
	int fd;

	/* stage 1 gets full control of console */
	if ((fd = open("/dev/console", O_RDWR)) == -1) {
		strerr_warn2(WARNING, "unable to open /dev/console: ",
				&strerr_sys);
	} else {
#ifdef TIOCSCTTY 
		ioctl(fd, TIOCSCTTY, (char *)0);
#endif
		dup2(fd, 0);
		if (fd > 2)
			close(fd);
	}
}

void runit()
{
	iopause_fd x;
#ifndef IOPAUSE_POLL
	fd_set rfds;
	struct timeval t;
#endif
	char ch;

	int st;
	const char * const stage_path[3] = {
		"/etc/runit/1",
		"/etc/runit/2",
		"/etc/runit/3"
	};

	sig_catch(sig_child, child_wait);
	sig_catch(sig_pwr, powerfail);

	for (st = 0; st < 3; st++) {
		if (st == 1) {
			sig_catch(sig_cont, stopit);
			sig_catch(sig_int, ctrlaltdel);
		} else {
			sig_catch(sig_cont, stage2_only);
			sig_catch(sig_int, stage2_only);
		}

		strerr_warn3(INFO, "enter stage: ", stage_path[st], 0);

		if (st == 0) {
			stage = add_child(fork_exec(stage_path[st],
						stage1_init));
		} else {
			stage = add_child(fork_exec(stage_path[st], 0));
		}

		sig_unblock(sig_cont);
		sig_unblock(sig_int);

		x.fd = selfpipe[0];
		x.events = IOPAUSE_READ;
		while (!child_stopped(stage)) {
#ifdef IOPAUSE_POLL
			poll(&x, 1, 14000);
#else
			t.tv_sec =14; t.tv_usec =0;
			FD_ZERO(&rfds);
			FD_SET(x.fd, &rfds);
			select(x.fd +1, &rfds, (fd_set*)0, (fd_set*)0, &t);
#endif

			while (read(selfpipe[0], &ch, 1) == 1);
		}

		sig_block(sig_cont);
		sig_block(sig_int);

		log_stage_exit(stage_path[st], stage->wstat);

		if (st == 0) {
			if (wait_crashed(stage->wstat) ||
					(wait_exitcode(stage->wstat) == 100))
			{
				strerr_warn2(WARNING, "skipping stage 2...", 0);
				st++;
				continue;
			}
		} else if (st == 1) {
			if (wait_crashed(stage->wstat) ||
					(wait_exitcode(stage->wstat) == 111))
			{
				strerr_warn2(WARNING,
						"killing all processes in stage 2...", 0);
				kill(-(stage->pid), 9);
				sleep(5);
				strerr_warn2(WARNING, "restarting.", 0);
				st--;
				continue;
			}
		}
	}

	sig_uncatch(sig_child);
	sig_uncatch(sig_cont);
	sig_uncatch(sig_int);
	sig_uncatch(sig_pwr);
}



/*****************************************************************************
 * Main Initialization
 *****************************************************************************/

int main (__attribute__((unused)) int argc,
		__attribute__((unused)) const char * const *argv,
		char * const *envp)
{
	pid_t pid;
	int fd;
	struct stat s;

	global_envp = envp;

	if (getpid() != 1) strerr_die2x(111, FATAL, "must be run as process no 1.");
	setsid();

	sig_block(sig_alarm);
	sig_block(sig_cont);
	sig_block(sig_hangup);
	sig_block(sig_int);
	sig_block(sig_pipe);
	//sig_block(sig_term);

	/* console */
	if ((fd = open_write("/dev/console")) != -1) {
		dup2(fd, 0);
		dup2(fd, 1);
		dup2(fd, 2);
		if (fd > 2)
			close(fd);
	}

	/* create selfpipe */
	while (pipe(selfpipe) == -1) {
		strerr_warn2(FATAL, "unable to create selfpipe, pausing: ", &strerr_sys);
		sleep(5);
	}
	coe(selfpipe[0]);
	coe(selfpipe[1]);
	ndelay_on(selfpipe[0]);
	ndelay_on(selfpipe[1]);

#ifdef RB_DISABLE_CAD
	/* activate ctrlaltdel handling, glibc, dietlibc */
	if (RB_DISABLE_CAD == 0) reboot_system(0);
#endif

	strerr_warn3(INFO, "This is Runit version 3.0.0a", ": booting.", 0);

	/* runit */
	runit();

#ifdef RB_AUTOBOOT
	/* fallthrough stage 3 */
	strerr_warn2(INFO, "sending KILL signal to all processes...", 0);
	kill(-1, SIGKILL);

	pid = fork();
	switch (pid) {
		case  0:
			__attribute__((fallthrough));
		case -1:
			if ((stat(REBOOT, &s) != -1) && (s.st_mode & S_IXUSR)) {
				strerr_warn2(INFO, "system reboot.", 0);
				sync();
				reboot_system(RB_AUTOBOOT);
			}
			else {
# ifdef RB_POWER_OFF
				strerr_warn2(INFO, "power off...", 0);
				sync();
				reboot_system(RB_POWER_OFF);
				sleep(2);
# endif
# ifndef UNGRACEFUL_DEATH
#  ifdef RB_HALT_SYSTEM
				strerr_warn2(INFO, "system halt.", 0);
				sync();
				reboot_system(RB_HALT_SYSTEM);
#  else
#   ifdef RB_HALT
				strerr_warn2(INFO, "system halt.", 0);
				sync();
				reboot_system(RB_HALT);
#   else
				strerr_warn2(INFO, "system reboot.", 0);
				sync();
				reboot_system(RB_AUTOBOOT);
#   endif
#  endif /* ifdef RB_HALT_SYSTEM */
# endif
			}
			if (pid == 0) _exit(0);
			break;
		default:
			while (wait_pid(0, pid) == -1);
	}
#endif /* ifdef RB_AUTOBOOT */

	for (;;) sig_pause();
	/* not reached */
	strerr_die2x(0, INFO, "exit.");
	return(0);
}
