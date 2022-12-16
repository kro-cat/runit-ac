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

AM_CFLAGS = $(WARN_CFLAGS) -Wall
build_prefix = $(top_builddir)/bin

bin_PROGRAMS = $(build_prefix)/chpst \
	       $(build_prefix)/runit \
	       $(build_prefix)/runit-init \
	       $(build_prefix)/runsv \
	       $(build_prefix)/runsvchdir \
	       $(build_prefix)/runsvdir \
	       $(build_prefix)/sv \
	       $(build_prefix)/svlogd \
	       $(build_prefix)/utmpset

noinst_LIBRARIES = $(build_prefix)/unix.a \
		   $(build_prefix)/byte.a \
		   $(build_prefix)/time.a

#include_HEADERS = library.h

__build_prefix_unix_a_SOURCES = alloc.c alloc_re.c buffer.c buffer_0.c buffer_1.c buffer_2.c buffer_get.c buffer_put.c buffer_read.c buffer_write.c coe.c env.c error.c error_str.c fd_copy.c fd_move.c fifo.c lock_ex.c lock_exnb.c ndelay_off.c ndelay_on.c open_append.c open_read.c open_trunc.c open_write.c openreadclose.c pathexec_env.c pathexec_run.c prot.c readclose.c seek_set.c sgetopt.c sig.c sig_block.c sig_catch.c sig_pause.c stralloc_cat.c stralloc_catb.c stralloc_cats.c stralloc_eady.c stralloc_opyb.c stralloc_opys.c stralloc_pend.c strerr_die.c strerr_sys.c subgetopt.c wait_nohang.c wait_pid.c
nodist___build_prefix_unix_a_SOURCES = alloc.h buffer.h byte.h coe.h env.h error.h fd.h fifo.h gen_alloc.h gen_allocdefs.h lock.h ndelay.h open.h pathexec.h prot.h readclose.h seek.h sgetopt.h sig.h str.h stralloc.h strerr.h subgetopt.h


__build_prefix_byte_a_SOURCES = byte_chr.c byte_copy.c byte_cr.c byte_diff.c byte_rchr.c fmt_uint.c fmt_uint0.c fmt_ulong.c scan_ulong.c str_chr.c str_diff.c str_len.c str_start.c
nodist___build_prefix_byte_a_SOURCES = byte.h fmt.h scan.h str.h


__build_prefix_time_a_SOURCES = iopause.c tai_now.c tai_pack.c tai_sub.c tai_unpack.c taia_add.c taia_approx.c taia_frac.c taia_less.c taia_now.c taia_pack.c taia_sub.c taia_uint.c
nodist___build_prefix_time_a_SOURCES = iopause.h select.h tai.h taia.h


__build_prefix__chpst_SOURCES = chpst.c uidgid.c
__build_prefix__chpst_LDFLAGS = unix.a byte.a
__build_prefix__chpst_LDADD = 


__build_prefix__runit_SOURCES = runit.c
__build_prefix__runit_LDFLAGS = unix.a byte.a -static
__build_prefix__runit_LDADD = 


__build_prefix__runit_init_SOURCES = runit-init.c
__build_prefix__runit_init_LDFLAGS = unix.a byte.a -static
__build_prefix__runit_init_LDADD = 


__build_prefix__runsv_SOURCES = runsv.c
__build_prefix__runsv_LDFLAGS = unix.a byte.a time.a
__build_prefix__runsv_LDADD = 


__build_prefix__runsvchdir_SOURCES = runsvchdir.c
__build_prefix__runsvchdir_LDFLAGS = unix.a byte.a
__build_prefix__runsvchdir_LDADD = 


__build_prefix__runsvdir_SOURCES = runsvdir.c
__build_prefix__runsvdir_LDFLAGS = unix.a byte.a time.a
__build_prefix__runsvdir_LDADD = 


__build_prefix__sv_SOURCES = sv.c
__build_prefix__sv_LDFLAGS = unix.a byte.a time.a
__build_prefix__sv_LDADD = 


__build_prefix__svlogd_SOURCES = svlogd.c pmatch.c fmt_ptime.c
# TODO: socket libs can be one of '', '-lxnet', and '-lsocket -lnsl'. Figure out how to switch between them.
__build_prefix__svlogd_LDFLAGS = unix.a byte.a time.a
__build_prefix__svlogd_LDADD = 


__build_prefix__utmpset_SOURCES = utmpset.c
__build_prefix__utmpset_LDFLAGS = unix.a byte.a
__build_prefix__utmpset_LDADD = 


check: $(IT)
	./check-local $(IT)

