srcdir = @srcdir@
VPATH = @srcdir@

AM_CFLAGS = $(WARN_CFLAGS) -Wall -I$(top_srcdir)/src
bindir = ../bin

bin_PROGRAMS = $(bindir)/chpst \
	       $(bindir)/runit \
	       $(bindir)/runit-init \
	       $(bindir)/runsv \
	       $(bindir)/runsvchdir \
	       $(bindir)/runsvdir \
	       $(bindir)/sv \
	       $(bindir)/svlogd

SUBDIRS = libs/byte libs/time libs/unix


__bindir__chpst_SOURCES = chpst.c uidgid.c
__bindir__chpst_LDFLAGS =
__bindir__chpst_LDADD = libs/unix/libunix.a libs/byte/libbyte.a


__bindir__runit_SOURCES = runit.c
__bindir__runit_LDFLAGS = -static
__bindir__runit_LDADD = libs/unix/libunix.a libs/byte/libbyte.a


__bindir__runit_init_SOURCES = runit-init.c
__bindir__runit_init_LDFLAGS = -static
__bindir__runit_init_LDADD = libs/unix/libunix.a libs/byte/libbyte.a


__bindir__runsv_SOURCES = runsv.c
__bindir__runsv_LDFLAGS =
__bindir__runsv_LDADD = libs/unix/libunix.a libs/byte/libbyte.a libs/time/libtime.a


__bindir__runsvchdir_SOURCES = runsvchdir.c
__bindir__runsvchdir_LDFLAGS =
__bindir__runsvchdir_LDADD = libs/unix/libunix.a libs/byte/libbyte.a


__bindir__runsvdir_SOURCES = runsvdir.c
__bindir__runsvdir_LDFLAGS =
__bindir__runsvdir_LDADD = libs/unix/libunix.a libs/byte/libbyte.a libs/time/libtime.a


__bindir__sv_SOURCES = sv.c
__bindir__sv_LDFLAGS =
__bindir__sv_LDADD = libs/unix/libunix.a libs/byte/libbyte.a libs/time/libtime.a


__bindir__svlogd_SOURCES = svlogd.c pmatch.c fmt_ptime.c
# TODO: socket s can be one of '', '-lxnet', and '-lsocket -lnsl'. Figure out how to switch between them.
__bindir__svlogd_LDFLAGS =
__bindir__svlogd_LDADD = libs/unix/libunix.a libs/byte/libbyte.a libs/time/libtime.a


if ENABLE_UTMPSET
bin_PROGRAMS += $(bindir)/utmpset
__bindir__utmpset_SOURCES = utmpset.c
__bindir__utmpset_LDFLAGS =
__bindir__utmpset_LDADD = libs/unix/libunix.a libs/byte/libbyte.a
endif


