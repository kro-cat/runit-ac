#ifndef WAIT_H
#define WAIT_H

extern int wait_pid(int *wstat, int pid);
extern int wait_nohang(int *wstat);
extern int wait_stop();
extern int wait_stopnohang();

#define wait_crashed(w) ((w) & 0x7f)
#define wait_exitcode(w) ((w) >> 8)
#define wait_stopsig(w) ((w) >> 8)
#define wait_stopped(w) (((w) & 0xff) == 0x7f)
#define wait_exited(w) (((w) & 0x7f) == 0)

#endif
