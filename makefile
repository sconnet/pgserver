#*****************************************************************************
#
# Copyright (C) 20012 Pear Gear, Inc.  All rights reserved.
#
# Programmer       : Steve Connet
#                    Feb. 8, 2001
#
# Source File Name : makefile
#
# Version          : $Id: make.default,v 1.1 2001/04/21 02:52:14 sconnet Exp sconnet $
#
# File Overview    : Makefile to make the Pear Gear server
#
# Revision History : 
#
# $Log: make.default,v $
# Revision 1.1  2001/04/21 02:52:14  sconnet
# Initial revision
#
#
#*****************************************************************************

target = pgserver

release = -O2 -Wall -D_REENTRANT -pthread -D_THREAD_SAFE
debug = -ggdb -D_REENTRANT -pthread -D_THREAD_SAFE
flags = $(release)
#flags = $(debug)

objects = pgserver.o \
          listen.o \
          acceptstats.o \
          acceptclient.o \
          config.o \
          thread.o \
          utils.o \
          client.o \
          connectcount.o \
          clientQ.o \
          workpool.o \
          work.o \
          pollclients.o

# build the target
$(target): $(objects)
	$(CXX) $(flags) -o $(target) $(objects)
	@echo "SETTING PERMISSIONS FOR DEVEL GROUP..."
	chmod 660 *.o
	chmod 770 $(target)

# build the objects
.cpp.o:
	$(CXX) $(flags) $*.cpp -c -o $@

depends: 
	rm -f makefile
	cp make.default makefile
	@echo "GENERATING DEPENDENCIES..."
	$(CXX) $(flags) -M *.cpp >> makefile

all:
	gmake clean
	gmake depends
	gmake

install:
	if [ -f pgserver ]; then cp pgserver /usr/local/bin; fi
	if [ -f pgserver.conf]; then cp pgserver.conf /etc; fi

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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h \
  acceptclient.h listen.h thread.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/time.h \
  /usr/include/bits/initspin.h client.h connectcount.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_iterator.h \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc \
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
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h \
  clientQ.h /usr/include/g++-3/queue \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_vector.h \
  /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_queue.h config.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h \
  acceptstats.h listen.h thread.h /usr/include/pthread.h \
  /usr/include/sched.h /usr/include/bits/time.h \
  /usr/include/bits/initspin.h client.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_function.h /usr/include/g++-3/stl_map.h \
  /usr/include/g++-3/stl_multimap.h /usr/include/g++-3/string \
  /usr/include/g++-3/std/bastring.h /usr/include/g++-3/cstddef \
  /usr/include/g++-3/std/straits.h /usr/include/g++-3/cctype \
  /usr/include/ctype.h /usr/include/g++-3/cstring \
  /usr/include/g++-3/alloc.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h client.h \
  /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/time.h \
  /usr/include/bits/initspin.h utils.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h /usr/include/sys/socket.h \
  /usr/include/bits/socket.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/sys/types.h \
  /usr/include/endian.h /usr/include/bits/endian.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h \
  /usr/include/string.h /usr/include/stdlib.h /usr/include/alloca.h
clientQ.o: clientQ.cpp pgserver.h /usr/include/g++-3/iostream \
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h clientQ.h \
  client.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_vector.h \
  /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_queue.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h config.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_config.h \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h \
  /usr/include/g++-3/cstring /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc utils.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h /usr/include/stdio.h \
  /usr/include/bits/stdio_lim.h /usr/include/bits/stdio.h \
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h \
  connectcount.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/g++-3/cstring \
  /usr/include/string.h /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/stdlib.h /usr/include/sys/types.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/include/assert.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_iterator.h \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc \
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
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h config.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h listen.h \
  thread.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h client.h config.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_config.h \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_function.h /usr/include/g++-3/stl_map.h \
  /usr/include/g++-3/stl_multimap.h /usr/include/g++-3/string \
  /usr/include/g++-3/std/bastring.h /usr/include/g++-3/cstddef \
  /usr/include/g++-3/std/straits.h /usr/include/g++-3/cctype \
  /usr/include/ctype.h /usr/include/g++-3/cstring \
  /usr/include/g++-3/alloc.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc \
  /usr/include/sys/time.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h /usr/include/netdb.h /usr/include/rpc/netdb.h \
  /usr/include/sys/socket.h /usr/include/bits/socket.h \
  /usr/include/bits/sockaddr.h /usr/include/asm/socket.h \
  /usr/include/asm/sockios.h /usr/include/bits/netdb.h \
  /usr/include/netinet/in.h /usr/include/stdint.h /usr/include/bits/in.h \
  /usr/include/bits/byteswap.h /usr/include/arpa/inet.h \
  /usr/include/fcntl.h /usr/include/bits/fcntl.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h config.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_config.h \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/stl_construct.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_map.h /usr/include/g++-3/stl_multimap.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h \
  /usr/include/g++-3/cstring /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/iterator /usr/include/g++-3/cassert \
  /usr/include/g++-3/std/bastring.cc acceptstats.h listen.h thread.h \
  client.h acceptclient.h connectcount.h clientQ.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_uninitialized.h \
  /usr/include/g++-3/stl_vector.h /usr/include/g++-3/stl_bvector.h \
  /usr/include/g++-3/stl_heap.h /usr/include/g++-3/stl_deque.h \
  /usr/include/g++-3/stl_queue.h workpool.h work.h pollclients.h \
  /usr/include/sys/stat.h /usr/include/bits/stat.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h \
  pollclients.h thread.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h client.h \
  /usr/include/g++-3/map /usr/include/g++-3/stl_tree.h \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_config.h \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_function.h /usr/include/g++-3/stl_map.h \
  /usr/include/g++-3/stl_multimap.h clientQ.h /usr/include/g++-3/queue \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_vector.h \
  /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_queue.h \
  /usr/include/sys/time.h /usr/include/unistd.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/confname.h \
  /usr/include/getopt.h /usr/include/fcntl.h /usr/include/bits/fcntl.h
test.o: test.cpp /usr/include/g++-3/fstream /usr/include/g++-3/fstream.h \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/bits/types.h \
  /usr/include/features.h /usr/include/sys/cdefs.h \
  /usr/include/gnu/stubs.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/wchar.h /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/g++-3/iostream /usr/include/g++-3/algorithm \
  /usr/include/g++-3/stl_algobase.h /usr/include/g++-3/stl_config.h \
  /usr/include/g++-3/stl_relops.h /usr/include/g++-3/stl_pair.h \
  /usr/include/g++-3/type_traits.h /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/time.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/bits/sigset.h \
  /usr/include/sys/sysmacros.h /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_tempbuf.h \
  /usr/include/g++-3/stl_algo.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/string /usr/include/g++-3/std/bastring.h \
  /usr/include/g++-3/cstddef /usr/include/g++-3/std/straits.h \
  /usr/include/g++-3/cctype /usr/include/ctype.h \
  /usr/include/g++-3/cstring /usr/include/g++-3/alloc.h \
  /usr/include/g++-3/stl_alloc.h /usr/include/assert.h \
  /usr/include/pthread.h /usr/include/sched.h /usr/include/bits/time.h \
  /usr/include/signal.h /usr/include/bits/initspin.h \
  /usr/include/bits/sigthread.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc
thread.o: thread.cpp /usr/include/sys/time.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h /usr/include/time.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/time.h /usr/include/bits/types.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/sys/select.h /usr/include/bits/select.h \
  /usr/include/bits/sigset.h pgserver.h /usr/include/g++-3/iostream \
  /usr/include/g++-3/iostream.h /usr/include/g++-3/streambuf.h \
  /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h \
  /usr/include/bits/wchar.h /usr/include/gconv.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stdarg.h \
  /usr/include/syslog.h /usr/include/sys/syslog.h /usr/include/signal.h \
  /usr/include/bits/signum.h /usr/include/bits/siginfo.h \
  /usr/include/bits/wordsize.h /usr/include/bits/sigaction.h \
  /usr/include/bits/sigcontext.h /usr/include/asm/sigcontext.h \
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h thread.h \
  /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/initspin.h
utils.o: utils.cpp utils.h /usr/include/unistd.h /usr/include/features.h \
  /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h \
  /usr/include/bits/posix_opt.h /usr/include/bits/types.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/stddef.h \
  /usr/include/bits/pthreadtypes.h /usr/include/bits/sched.h \
  /usr/include/bits/confname.h /usr/include/getopt.h \
  /usr/include/string.h /usr/include/ctype.h /usr/include/endian.h \
  /usr/include/bits/endian.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h work.h \
  thread.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h clientQ.h \
  client.h /usr/include/g++-3/queue /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_vector.h \
  /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_queue.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_map.h \
  /usr/include/g++-3/stl_multimap.h /usr/include/g++-3/string \
  /usr/include/g++-3/std/bastring.h /usr/include/g++-3/cstddef \
  /usr/include/g++-3/std/straits.h /usr/include/g++-3/cctype \
  /usr/include/ctype.h /usr/include/g++-3/cstring \
  /usr/include/g++-3/alloc.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc utils.h \
  /usr/include/unistd.h /usr/include/bits/posix_opt.h \
  /usr/include/bits/confname.h /usr/include/getopt.h pollclients.h \
  /usr/include/g++-3/algorithm /usr/include/g++-3/stl_tempbuf.h \
  /usr/include/g++-3/stl_algo.h /usr/include/sys/socket.h \
  /usr/include/bits/socket.h /usr/include/bits/sockaddr.h \
  /usr/include/asm/socket.h /usr/include/asm/sockios.h
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
  /usr/include/bits/sigstack.h /usr/include/bits/sigthread.h workpool.h \
  work.h thread.h /usr/include/pthread.h /usr/include/sched.h \
  /usr/include/bits/time.h /usr/include/bits/initspin.h \
  /usr/include/g++-3/queue /usr/include/g++-3/stl_algobase.h \
  /usr/include/g++-3/stl_config.h /usr/include/g++-3/stl_relops.h \
  /usr/include/g++-3/stl_pair.h /usr/include/g++-3/type_traits.h \
  /usr/include/string.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/limits.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/syslimits.h \
  /usr/include/limits.h /usr/include/bits/posix1_lim.h \
  /usr/include/bits/local_lim.h /usr/include/linux/limits.h \
  /usr/include/bits/posix2_lim.h /usr/include/stdlib.h \
  /usr/include/sys/types.h /usr/include/endian.h \
  /usr/include/bits/endian.h /usr/include/sys/select.h \
  /usr/include/bits/select.h /usr/include/sys/sysmacros.h \
  /usr/include/alloca.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new.h \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/new \
  /usr/lib/gcc-lib/i386-redhat-linux/2.96/include/exception \
  /usr/include/g++-3/stl_iterator.h /usr/include/g++-3/stl_alloc.h \
  /usr/include/assert.h /usr/include/g++-3/stl_construct.h \
  /usr/include/g++-3/stl_uninitialized.h /usr/include/g++-3/stl_vector.h \
  /usr/include/g++-3/stl_bvector.h /usr/include/g++-3/stl_heap.h \
  /usr/include/g++-3/stl_deque.h /usr/include/g++-3/stl_function.h \
  /usr/include/g++-3/stl_queue.h config.h /usr/include/g++-3/map \
  /usr/include/g++-3/stl_tree.h /usr/include/g++-3/stl_map.h \
  /usr/include/g++-3/stl_multimap.h /usr/include/g++-3/string \
  /usr/include/g++-3/std/bastring.h /usr/include/g++-3/cstddef \
  /usr/include/g++-3/std/straits.h /usr/include/g++-3/cctype \
  /usr/include/ctype.h /usr/include/g++-3/cstring \
  /usr/include/g++-3/alloc.h /usr/include/g++-3/iterator \
  /usr/include/g++-3/cassert /usr/include/g++-3/std/bastring.cc \
  /usr/include/unistd.h /usr/include/bits/posix_opt.h \
  /usr/include/bits/confname.h /usr/include/getopt.h
