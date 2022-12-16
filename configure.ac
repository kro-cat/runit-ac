#
#  MIT License
#
#  Copyright (c) 2022 Kara
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.
#

AC_PREREQ([2.69])
AC_INIT([runit], [0.1.0], [bugs@kara-online.net], [runit])

m4_include([m4/ax_valgrind_check.m4])

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


#autoconf stuff
AM_INIT_AUTOMAKE([subdir-objects])
WARN_CFLAGS="-W -Wall -Wunused -Werror"
AC_SUBST(WARN_CFLAGS)
AC_CONFIG_MACRO_DIRS([m4])
#AC_CONFIG_SUBDIRS([include/krossock])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])
AX_VALGRIND_DFLT([memcheck], [on])
AX_VALGRIND_CHECK

#program config
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
AC_CHECK_HEADERS([utmp.h])
AC_CHECK_HEADERS([utmpx.h])

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

AC_LANG([C])
AC_MSG_CHECKING([for short setgroups])
AC_RUN_IFELSE([AC_LANG_PROGRAM([[]],
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

#makefiles
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  tests/Makefile
  include/Makefile
])
AC_OUTPUT
