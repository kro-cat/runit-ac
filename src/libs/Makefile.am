srcdir = @srcdir@
VPATH = @srcdir@

AM_CFLAGS = $(WARN_CFLAGS) -Wall -I$(top_srcdir)/src/include

noinst_LIBRARIES= libunix.a libbyte.a libtime.a


libunix_a_SOURCES = alloc.c alloc_re.c buffer.c buffer_0.c buffer_1.c buffer_2.c buffer_get.c buffer_put.c buffer_read.c buffer_write.c coe.c env.c error.c error_str.c fd_copy.c fd_move.c fifo.c lock_ex.c lock_exnb.c ndelay_off.c ndelay_on.c open_append.c open_read.c open_trunc.c open_write.c openreadclose.c pathexec_env.c pathexec_run.c prot.c readclose.c seek_set.c sgetopt.c sig.c sig_block.c sig_catch.c sig_pause.c stralloc_cat.c stralloc_catb.c stralloc_cats.c stralloc_eady.c stralloc_opyb.c stralloc_opys.c stralloc_pend.c strerr_die.c strerr_sys.c subgetopt.c wait_nohang.c wait_pid.c
#nodist_libunix_a_SOURCES = alloc.h buffer.h byte.h coe.h env.h error.h fd.h fifo.h gen_alloc.h gen_allocdefs.h lock.h ndelay.h open.h pathexec.h prot.h readclose.h seek.h sgetopt.h sig.h str.h stralloc.h strerr.h subgetopt.h


libbyte_a_SOURCES = byte_chr.c byte_copy.c byte_cr.c byte_diff.c byte_rchr.c fmt_uint.c fmt_uint0.c fmt_ulong.c scan_ulong.c str_chr.c str_diff.c str_len.c str_start.c
#nodist_libbyte_a_SOURCES = byte.h fmt.h scan.h str.h


libtime_a_SOURCES = iopause.c tai_now.c tai_pack.c tai_sub.c tai_unpack.c taia_add.c taia_approx.c taia_frac.c taia_less.c taia_now.c taia_pack.c taia_sub.c taia_uint.c
#nodist_libtime_a_SOURCES = iopause.h select.h tai.h taia.h

