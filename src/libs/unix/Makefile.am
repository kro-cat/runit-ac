srcdir = @srcdir@
VPATH = @srcdir@

AM_CFLAGS = $(WARN_CFLAGS) -Wall -I$(top_srcdir)/src

noinst_LIBRARIES= libunix.a

libunix_a_SOURCES = alloc.c buffer.c coe.c env.c fd.c fifo.c lock.c ndelay.c open.c openreadclose.c pathexec.c prot.c readclose.c seek.c sgetopt.c sig.c stralloc.c strerr.c subgetopt.c wait.c
#nodist_libunix_a_SOURCES = alloc.h buffer.h coe.h env.h fd.h fifo.h gen_allocdefs.h gen_alloc.h lock.h ndelay.h open.h openreadclose.h pathexec.h prot.h readclose.h seek.h sgetopt.h sig.h stralloc.h strerr.h subgetopt.h
