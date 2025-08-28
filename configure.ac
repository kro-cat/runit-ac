m4_define([runit_VERSION], [3.0.0-alpha.2])
AC_PREREQ([2.69])
AC_INIT([runit], m4_defn([runit_VERSION]), [], [runit-]m4_defn([runit_VERSION]))
AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.16.0 subdir-objects foreign no-dependencies])

AC_ARG_ENABLE(debug,
  [AS_HELP_STRING([--enable-debug], [Enable debug messages (default is no)])],
  [
    AC_MSG_NOTICE([debug messages will be enabled])
    AC_DEFINE([DEBUG], [], [enable debug messages])
  ]
)

AC_ARG_ENABLE(utmpset,
[AS_HELP_STRING([--disable-utmpset], [disable utmpset build])],
  [
    AC_MSG_NOTICE([utmpset will not be built])
    enable_utmpset=no
  ],
  [enable_utmpset=yes]
)
AM_CONDITIONAL([ENABLE_UTMPSET], [test "x${enable_utmpset}" = "xyes"])

AC_ARG_ENABLE(container-mode,
[AS_HELP_STRING([--enable-container-mode], [run as non-root, disable pid 1 enforcement, don't sync on shutdown, disable kernel halt and reboot commands])],
  [
    AC_MSG_WARN([CONTAINER MODE IS ENABLED, DO NOT USE THIS AS A REAL INIT HANDLER])
    AC_DEFINE([CONTAINER_MODE], [], [Make runit act like a normal program])
  ]
)

#host switch
AC_CANONICAL_HOST

AS_CASE(["$host_os"],
  [*linux*], [
    # OS specific stuff here
  ],
#  [*mingw*|*cygwin*], [
#   # OS specific stuff here
#    AC_DEFINE([WINVER], [_WIN32_WINNT_WIN10],
#      [Define windows version as WIN10])
#    AC_DEFINE([_WIN32_WINNT], [_WIN32_WINNT_WIN10],
#      [Define windows version as WIN10])
#  ],
  [AC_MSG_WARN([unsupported system: $host_os])]
)

# tests that need to be implemented
#iopause
#select
#reboot_system
#uw_tmp.h
#socket libs
# may be '', '-lxnet', or '-lsocket -lnsl'

#program config
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

#headers
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADERS([sys/file.h])
AC_CHECK_HEADERS([sys/ioctl.h])
AC_CHECK_HEADERS([sys/param.h])
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([sys/time.h])
AC_CHECK_HEADERS([unistd.h])
AS_IF([test "x${enable_utmpset}" = "xyes"],
  [
    AC_MSG_CHECKING([for utmp headers])
    AC_LANG_PUSH([C])
    AC_CHECK_HEADERS([utmpx.h],
      [
        AC_MSG_RESULT(utmpx.h)
        AC_MSG_CHECKING([for utmp struture type])
        AC_CHECK_TYPES([struct futmpx],
          [
            AC_MSG_RESULT(struct futmpx)
            AC_DEFINE([STRUCT_UTMP], [struct futmpx], [Define if struct futmpx.])
          ],
          [AC_CHECK_TYPES([struct utmpx],
            [
              AC_MSG_RESULT(struct utmpx)
              AC_DEFINE([STRUCT_UTMP], [struct utmpx], [Define if struct utmp.])
            ],
            [AC_CHECK_TYPES([struct utmp],
              [
                AC_MSG_RESULT(struct utmpx)
                AC_DEFINE([STRUCT_UTMP], [struct utmp], [Define if struct utmp.])
              ],
              [
                AC_MSG_RESULT(unknown)
                AC_MSG_FAILURE([couldn't figure out utmp struct name])
              ],
              [[#define __USE__GNU
                #include <utmpx.h>
              ]]
            )],
            [[#include <utmpx.h>
            ]]
          )],
          [[#include <utmpx.h>
          ]]
        )
      ],
      [AC_CHECK_HEADERS([utmp.h],
        [
          AC_MSG_RESULT(utmp.h)
          AC_CHECK_TYPES([struct utmp],
            [AC_DEFINE([UTMP_STRUCT], [struct utmp], [Define if struct utmp.])],
            [AC_MSG_FAILURE([couldn't figure out utmp struct name])],
            [[#include <utmp.h>
            ]]
          )
        ],
        [
          AC_MSG_RESULT(not found)
          AC_MSG_FAILURE([one of utmp.h or utmpx.h is required to build svlogd])
        ]
      )]
    )
    AC_LANG_POP([C])
  ]
)

#types
AC_TYPE_UINT64_T
AC_TYPE_OFF_T
AC_TYPE_UID_T

#functions
AC_FUNC_FORK
AC_FUNC_GETGROUPS
AC_FUNC_MALLOC
AC_CHECK_FUNCS([dup2])
AC_CHECK_FUNCS([fchdir])
AC_CHECK_FUNCS([ftruncate])
AC_CHECK_FUNCS([gettimeofday])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([mkdir])
AC_CHECK_FUNCS([select])
AC_CHECK_FUNCS([socket])
AC_CHECK_FUNCS([flock],
  [
    AC_DEFINE_UNQUOTED([HASFLOCK], 1, [Define if flock exists.])
  ]
)
AC_CHECK_FUNCS([mkfifo],
  [
    AC_DEFINE_UNQUOTED([HASMKFIFO], 1, [Define if mkfifo exists.])
  ]
)
AC_CHECK_FUNCS([sigaction],
  [
    AC_DEFINE_UNQUOTED([HASSIGACTION], 1, [Define if sigaction exists.])
  ]
)
AC_CHECK_FUNCS([sigprocmask],
  [
    AC_DEFINE_UNQUOTED([HASSIGPROCMASK], 1, [Define if sigprocmask exists.])
  ]
)

AC_MSG_CHECKING([for POSIX setgroups])
AC_LANG_PUSH([C])
AC_RUN_IFELSE(
  [AC_LANG_PROGRAM(
    [[
      #include <sys/types.h>
      #include <unistd.h>
      #include <grp.h>
    ]],
    [[
      short x[4];
      x[0] = x[1] = 1;
      if (getgroups(1,x)==0) if (setgroups(1,x)==-1) _exit(1);
      if (getgroups(1,x)==-1) _exit(1);
      if (x[1]!=1) _exit(1);
      x[1]=2;
      if (getgroups(1,x)==-1) _exit(1);
      if (x[1]!=2) _exit(1);
      _exit(0);
    ]]
  )],
  [
    AC_MSG_RESULT([yes])
    AC_DEFINE_UNQUOTED([HASPOSIXSETGROUPS], 1, [Define if POSIX setgroups works])
  ],
  [
    AC_MSG_RESULT([no])
  ]
)
AC_LANG_POP([C])

AC_MSG_CHECKING([for number of reboot arguments])
AC_LANG_PUSH([C])
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [[
      #include <unistd.h>
      #include <sys/reboot.h>
    ]],
    [[
      return(reboot(what, (char *)0));
    ]]
  )],
  [
    AC_MSG_RESULT([2])
    AC_DEFINE_UNQUOTED([NONSTDREBOOT], 1, [Define if non-standard reboot.])
  ],
  [
    AC_MSG_RESULT([1])
  ]
)
AC_LANG_POP([C])

#makefiles
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/libs/byte/Makefile
  src/libs/time/Makefile
  src/libs/unix/Makefile
])

m4_include([m4/ax_valgrind_check.m4])
AX_VALGRIND_DFLT([memcheck], [on])
AX_VALGRIND_CHECK

AC_OUTPUT

# vim: ft=m4 ts=2 sts=2 sw=2 et
