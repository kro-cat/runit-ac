AC_PREREQ([2.69])
AC_INIT([runit], [0.2.0], [bugs@kara-online.net], [runit])
AC_CONFIG_MACRO_DIRS([m4])
#AC_CONFIG_SUBDIRS([include/krossock])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.16.0 subdir-objects foreign no-dependencies])

AC_ARG_ENABLE(debug,
  [AS_HELP_STRING([--enable-debug], [Enable debug messages (default is no)])],
  [enable_debug=$enableval],
  [enable_debug=no]
)

if test "x$enable_debug" = "xyes"; then
  AC_DEFINE([DEBUG], [], [enable debug messages])
  AC_MSG_NOTICE([debug messages will be enabled])
fi

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
AC_LANG_PUSH([C])
AC_CHECK_HEADERS([utmpx.h],
  [
    AC_CHECK_TYPES([struct futmpx],
      [
        AC_DEFINE([STRUCT_UTMP], [struct futmpx], [Define if struct futmpx.])
      ],
      [
        AC_CHECK_TYPES([struct utmpx],
          [
            AC_DEFINE([STRUCT_UTMP], [struct utmpx], [Define if struct utmp.])
          ],
          [
            AC_CHECK_TYPES([struct utmp],
              [
                AC_DEFINE([STRUCT_UTMP], [struct utmp], [Define if struct utmp.])
              ],
              [
                AC_MSG_FAILURE([couldn't figure out utmp struct name])
              ],
              [[
                #define __USE__GNU
                #include <utmpx.h>
              ]]
            )
          ],
          [[
            #include <utmpx.h>
          ]]
        )
      ],
      [[
        #include <utmpx.h>
      ]]
    )
  ],
  [
    AC_CHECK_HEADERS([utmp.h],
      [
        AC_CHECK_TYPES([struct utmp],
          [
            AC_DEFINE([UTMP_STRUCT], [struct utmp], [Define if struct utmp.])
          ],
          [
            AC_MSG_FAILURE([couldn't figure out utmp struct name])
          ],
          [[
            #include <utmp.h>
          ]]
        )
      ],
      [AC_MSG_FAILURE([one of utmp.h or utmpx.h is required to build svlogd])]
    )
  ]
)
AC_LANG_POP([C])

#types
AC_TYPE_UINT64_T
AC_TYPE_OFF_T
AC_TYPE_UID_T

#functions
AC_FUNC_FORK
AC_FUNC_GETGROUPS
AC_FUNC_MALLOC
AC_FUNC_WAIT3
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
AC_CHECK_FUNCS([waitpid],
  [
    AC_DEFINE_UNQUOTED([HASWAITPID], 1, [Define if waitpid exists.])
  ]
)

AC_MSG_CHECKING([for short setgroups])
AC_LANG_PUSH([C])
AC_RUN_IFELSE([AC_LANG_PROGRAM(
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
  ]])],
  [
    AC_MSG_RESULT([yes])
    AC_DEFINE_UNQUOTED([HASSHORTSETGROUPS], 1, [Define if short setgroups works])
  ],
  [
    AC_MSG_RESULT([no])
  ]
)
AC_LANG_POP([C])

AC_MSG_CHECKING([for number of reboot arguments])
AC_LANG_PUSH([C])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
  [[
    #include <unistd.h>
    #include <sys/reboot.h>
  ]],
  [[
    return(reboot(what, (char *)0));
  ]])],
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
  src/libs/Makefile
])

m4_include([m4/ax_valgrind_check.m4])
AX_VALGRIND_DFLT([memcheck], [on])
AX_VALGRIND_CHECK

AC_OUTPUT
