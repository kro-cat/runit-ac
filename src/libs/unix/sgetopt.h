#ifndef SGETOPT_H
#define SGETOPT_H

#include "subgetopt.h"

#ifndef SGETOPTNOSHORT
#define getopt sgetoptmine
#define opterr sgetopterr
#define optprogname sgetoptprogname

#define optarg subgetoptarg
#define optind subgetoptind
#define optpos subgetoptpos
#define optproblem subgetoptproblem
#define opteof subgetoptdone
#endif

extern int sgetoptmine(int,const char *const *,const char *);
extern int sgetopterr;
extern const char *sgetoptprogname;

#endif
