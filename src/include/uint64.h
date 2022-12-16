
/* Public domain. */

#ifndef UINT64_H
#define UINT64_H

#ifdef HAVE_UINT64_T
typedef uint64_t uint64;
#else
#if __WORDSIZE == 64
typedef unsigned long int uint64;
#else
typedef unsigned long long int uint64;
#endif
#endif

#endif
