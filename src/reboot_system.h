#include <unistd.h>
#include <sys/reboot.h>

/* sysdep: -std reboot */

int reboot_system(int what) {
  return(reboot(what, (char *)0));
}
#include <unistd.h>
#include <sys/reboot.h>

/* sysdep: +std reboot */

int reboot_system(int what) {
  return(reboot(what));
}
