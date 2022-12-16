#include <unistd.h>
#include <sys/reboot.h>

int reboot_system(int what) {
#ifdef NONSTDREBOOT
  return(reboot(what, (char *)0));
#else
  return(reboot(what));
#endif
}

/* vim: set sts=2 ts=2 tw=2 et : */
