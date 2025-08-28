#include <config.h>
#include <sys/types.h>

#ifdef HAVE_UTMPX_H

# define __USE_GNU
# include <utmpx.h>

# ifdef _PATH_UTMPX
#  define UW_TMP_UFILE _PATH_UTMPX
#  define UW_TMP_WFILE _PATH_WTMPX
# else /* ifdef _PATH_UTMPX */
/* AIX only has UTMP_FILE */
#  ifdef UTMPX_FILE
#   define UW_TMP_UFILE UTMPX_FILE
#   define UW_TMP_WFILE WTMPX_FILE
#  else /* ifdef _UTMPX_FILE */
#   error neither _PATH_UTMPX nor UTMPX_FILE defined.
#  endif /* ifdef _UTMPX_FILE */
# endif /* ifdef _PATH_UTMPX */

/* Backwards compatibility hacks.  */
# define ut_name ut_user
# ifndef _NO_UT_TIME
/* We have a problem here: `ut_time' is also used otherwise.  Define
   _NO_UT_TIME if the compiler complains.  */
#  define ut_time ut_tv.tv_sec
# endif /* ifndef _NO_UT_TIME */

# define ut_xtime ut_tv.tv_sec
# define ut_addr ut_addr_v6[0]

#else /* ifdef HAVE_UTMPX_H */
# ifndef HAVE_UTMP_H
#  error one of utmpx.h or utmp.h is required for svlogd.
# endif /* ifndef HAVE_UTMP_H */

# include <utmp.h>

# ifdef _PATH_UTMP
#  define UW_TMP_UFILE _PATH_UTMP
#  define UW_TMP_WFILE _PATH_WTMP
# else /* ifdef _PATH_UTMP */
/* AIX only has UTMP_FILE */
#  ifdef UTMP_FILE
#   define UW_TMP_UFILE UTMP_FILE
#   define UW_TMP_WFILE WTMP_FILE
#  else /* ifndef UTMP_FILE */
#   error neither _PATH_UTMP nor UTMP_FILE defined.
#  endif /* ifndef UTMP_FILE */
# endif /* ifdef _PATH_UTMP */

#endif /* ifdef HAVE_UTMPX_H */

/* configure figured this out for us */
typedef STRUCT_UTMP uw_tmp;
