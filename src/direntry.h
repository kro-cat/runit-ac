/* Public domain. */

#ifndef DIRENTRY_H
#define DIRENTRY_H

/* sysdep: -dirent */

#include <sys/types.h>
#include <sys/dir.h>
#define direntry struct direct

#endif
/* Public domain. */

#ifndef DIRENTRY_H
#define DIRENTRY_H

/* sysdep: +dirent */

#include <sys/types.h>
#include <dirent.h>
#define direntry struct dirent

#endif
