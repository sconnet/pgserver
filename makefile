#*****************************************************************************
#
# Copyright (C) 20012 Pear Gear, Inc.  All rights reserved.
#
# Programmer       : Steve Connet
#                    Feb. 8, 2001
#
# Source File Name : makefile
#
# Version          : $Id: makefile,v 1.2 2001/04/21 06:15:31 sconnet Exp sconnet $
#
# File Overview    : Makefile to make the Pear Gear server
#
# Revision History : 
#
# $Log: makefile,v $
# Revision 1.2  2001/04/21 06:15:31  sconnet
# performed a make depends
#
# Revision 1.1  2001/04/21 02:52:14  sconnet
# Initial revision
#
#
#*****************************************************************************

target = pgserver

standard = -Wall -D_REENTRANT -D_THREAD_SAFE -pthread
release = -O2 $(standard)
debug = -ggdb -D_DEBUG $(standard)
trace = -D_TRACE $(debug)

#flags = $(release)
flags = $(debug)
#flags = $(trace)

objects = pgserver.o \
          listen.o \
          acceptstats.o \
          acceptclient.o \
          config.o \
          pgconfig.o \
          thread.o \
          utils.o \
          client.o \
          connectcount.o \
          workpool.o \
          work.o \
          pollclients.o \
          workloginQ.o \
          workcommQ.o

# build the target
$(target): $(objects)
	$(CXX) $(flags) -o $(target) $(objects) -lpthread
	@chmod 660 *.o
	@chmod 770 $(target)

# build the objects
.cpp.o:
	$(CXX) $(flags) $*.cpp -c -o $@

depends: 
	@rm -f makefile
	@cp make.default makefile
	$(CXX) $(flags) -M *.cpp >> makefile

all:
	gmake clean
	gmake depends
	gmake

install:
	if [ -f pgserver ]; then cp pgserver /usr/local/bin; fi
	if [ -f pgserver.conf ]; then cp pgserver.conf /etc; fi

clean: 
	@if [ -f $(target) ]; then rm $(target); fi
	@for file in $(objects); do \
		if [ -f $$file ]; then \
			rm $$file; \
		fi; \
	done

# automatically generated dependencies
acceptclient.o: acceptclient.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h acceptclient.h listen.h thread.h client.h lock.h \
  connectcount.h /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h safeQ.h \
  pgconfig.h config.h /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h
acceptstats.o: acceptstats.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h acceptstats.h listen.h thread.h client.h lock.h \
  pgconfig.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h
client.o: client.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h client.h lock.h /usr/include/sys/socket.h \
  /usr/include/bits/socket.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h
config.o: config.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  /usr/include/stdio.h /usr/include/bits/stdio_lim.h \
  /usr/include/g++-3/fstream /usr/include/g++-3/fstream.h \
  /usr/include/g++-3/algorithm /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_tempbuf.h /usr/include/g++-3/stl_algo.h \
  /usr/include/g++-3/stl_heap.h
connectcount.o: connectcount.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h connectcount.h lock.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h \
  pgconfig.h config.h
listen.o: listen.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h listen.h thread.h client.h lock.h pgconfig.h \
  config.h /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h \
  /usr/include/sys/time.h /usr/include/netdb.h /usr/include/rpc/netdb.h \
  /usr/include/sys/socket.h /usr/include/bits/socket.h \
  /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
  /usr/include/asm/sockios.h /usr/include/bits/netdb.h \
  /usr/include/netinet/in.h /usr/include/stdint.h /usr/include/bits/in.h \
  /usr/include/bits/byteswap.h /usr/include/arpa/inet.h \
  /usr/include/fcntl.h /usr/include/bits/fcntl.h
pgconfig.o: pgconfig.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h pgconfig.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h
pgserver.o: pgserver.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h pgconfig.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  acceptstats.h listen.h thread.h client.h acceptclient.h connectcount.h \
  safeQ.h /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h workpool.h work.h pollclients.h \
  /usr/include/sys/stat.h /usr/include/bits/stat.h
pollclients.o: pollclients.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h pollclients.h thread.h lock.h client.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h safeQ.h \
  pgconfig.h config.h /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h /usr/include/sys/time.h \
  /usr/include/fcntl.h /usr/include/bits/fcntl.h
test.o: test.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h pgconfig.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  acceptstats.h listen.h thread.h client.h acceptclient.h connectcount.h \
  safeQ.h /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h workpool.h work.h pollclients.h \
  /usr/include/g++-3/fstream /usr/include/g++-3/fstream.h \
  /usr/include/g++-3/algorithm /usr/include/g++-3/stl_tempbuf.h \
  /usr/include/g++-3/stl_algo.h
thread.o: thread.cpp utils.h /usr/include/g++-3/string \
  /usr/include/g++-3/std/bastring.h /usr/include/g++-3/cstddef \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/g++-3/std/straits.h /usr/include/g++-3/cctype \
  /usr/include/ctype.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h /usr/include/bits/types.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/endian.h /usr/include/bits/endian.h \
  /usr/include/g++-3/cstring /usr/include/string.h \
  /usr/include/g++-3/alloc.h /usr/include/g++-3/stl_config.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/assert.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/time.h /usr/include/signal.h \
  /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h thread.h
utils.o: utils.cpp utils.h /usr/include/g++-3/string \
  /usr/include/g++-3/std/bastring.h /usr/include/g++-3/cstddef \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/g++-3/std/straits.h /usr/include/g++-3/cctype \
  /usr/include/ctype.h /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h /usr/include/bits/types.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/endian.h /usr/include/bits/endian.h \
  /usr/include/g++-3/cstring /usr/include/string.h \
  /usr/include/g++-3/alloc.h /usr/include/g++-3/stl_config.h \
  /usr/include/_G_config.h /usr/include/wchar.h /usr/include/bits/wchar.h \
  /usr/include/gconv.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/stdlib.h /usr/include/sys/types.h /usr/include/time.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h /usr/include/assert.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/time.h /usr/include/signal.h \
  /usr/include/bits/initspin.h /usr/include/bits/sigthread.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/cstdio /usr/include/stdio.h \
  /usr/include/bits/stdio_lim.h /usr/include/sys/time.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h
workcommQ.o: workcommQ.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h workcommQ.h work.h thread.h safeQ.h pgconfig.h \
  config.h /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h client.h pollclients.h
work.o: work.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h work.h thread.h safeQ.h pgconfig.h config.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h client.h pollclients.h \
  /usr/include/g++-3/algorithm /usr/include/g++-3/stl_tempbuf.h \
  /usr/include/g++-3/stl_algo.h /usr/include/sys/socket.h \
  /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h
workloginQ.o: workloginQ.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h workloginQ.h work.h thread.h safeQ.h pgconfig.h \
  config.h /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  /usr/include/errno.h /usr/include/bits/errno.h \
  /usr/include/linux/errno.h /usr/include/asm/errno.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h client.h pollclients.h
workpool.o: workpool.cpp pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/sigset.h /usr/include/bits/signum.h \
  /usr/include/time.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h utils.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h workpool.h work.h thread.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_vector.h \
  /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_queue.h pgconfig.h config.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h lock.h \
  workloginQ.h workcommQ.h
