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

# BINARY EXECUTABLE
#AM_CFLAGS = $(WARN_CFLAGS) -I$(top_builddir)/include/krossock/src
#bin_PROGRAMS = $(top_builddir)/bin/program
#__top_builddir__bin_program_SOURCES = program.c
#__top_builddir__bin_program_LDFLAGS = -static-libgcc -static $(top_builddir)/include/krossock/bin/libkrossock.a
#__top_builddir__bin_program_LDADD = -lkrossock -lssl -lcrypto

# LIBRARY
#noinst_LIBRARIES = $(top_builddir)/bin/library.a
#__top_builddir__bin_library_a_SOURCES = library.c
#include_HEADERS = library.h

AM_CFLAGS = $(WARN_CFLAGS) -Wall -I$(top_srcdir)/src/include
bindir = ../bin

bin_PROGRAMS = $(bindir)/chpst \
	       $(bindir)/runit \
	       $(bindir)/runit-init \
	       $(bindir)/runsv \
	       $(bindir)/runsvchdir \
	       $(bindir)/runsvdir \
	       $(bindir)/sv \
	       $(bindir)/svlogd \
	       $(bindir)/utmpset

SUBDIRS = libs


__bindir__chpst_SOURCES = chpst.c uidgid.c
__bindir__chpst_LDFLAGS =
__bindir__chpst_LDADD = libs/libunix.a libs/libbyte.a


__bindir__runit_SOURCES = runit.c
__bindir__runit_LDFLAGS = -static
__bindir__runit_LDADD = libs/libunix.a libs/libbyte.a


__bindir__runit_init_SOURCES = runit-init.c
__bindir__runit_init_LDFLAGS = -static
__bindir__runit_init_LDADD = libs/libunix.a libs/libbyte.a


__bindir__runsv_SOURCES = runsv.c
__bindir__runsv_LDFLAGS =
__bindir__runsv_LDADD = libs/libunix.a libs/libbyte.a libs/libtime.a


__bindir__runsvchdir_SOURCES = runsvchdir.c
__bindir__runsvchdir_LDFLAGS =
__bindir__runsvchdir_LDADD = libs/libunix.a libs/libbyte.a


__bindir__runsvdir_SOURCES = runsvdir.c
__bindir__runsvdir_LDFLAGS =
__bindir__runsvdir_LDADD = libs/libunix.a libs/libbyte.a libs/libtime.a


__bindir__sv_SOURCES = sv.c
__bindir__sv_LDFLAGS =
__bindir__sv_LDADD = libs/libunix.a libs/libbyte.a libs/libtime.a


__bindir__svlogd_SOURCES = svlogd.c pmatch.c fmt_ptime.c
# TODO: socket s can be one of '', '-lxnet', and '-lsocket -lnsl'. Figure out how to switch between them.
__bindir__svlogd_LDFLAGS =
__bindir__svlogd_LDADD = libs/libunix.a libs/libbyte.a libs/libtime.a


__bindir__utmpset_SOURCES = utmpset.c
__bindir__utmpset_LDFLAGS =
__bindir__utmpset_LDADD = libs/libunix.a libs/libbyte.a


