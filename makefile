CC		= gcc
CFLAGS		= -Wall -g -I/opt/local/include -O
LIBS		= -L/opt/local/lib -lusb

COMMON_OBJS     = target.o
COMMON_OBJS     += adapter-usb.o
COMMON_OBJS	+= adapter-lpt.o
COMMON_OBJS	+= adapter-bitbang.o
COMMON_OBJS	+= adapter-mpsse.o

PROG_OBJS	= mcprog.o conf.o $(COMMON_OBJS)

REMOTE_OBJS	= gdbproxy.o rpmisc.o remote-elvees.o $(COMMON_OBJS)

all:		mcprog mcremote #adapter-bitbang adapter-mpsse

mcprog:		$(PROG_OBJS)
		$(CC) -o $@ $(PROG_OBJS) $(LIBS)

mcremote:	$(REMOTE_OBJS)
		$(CC) -o $@ $(REMOTE_OBJS) $(LIBS)

adapter-bitbang: adapter-bitbang.c
		$(CC) $(CFLAGS) -DSTANDALONE -o $@ adapter-bitbang.c $(LIBS)

adapter-mpsse: adapter-mpsse.c
		$(CC) $(CFLAGS) -DSTANDALONE -o $@ adapter-mpsse.c $(LIBS)

clean:
		rm -f *~ *.o core mcprog mcprog.exe adapter-bitbang adapter-mpsse

install:	mcprog mcprog.conf
		install -c -s mcprog /usr/local/bin/mcprog
		[ -f //usr/local/etc/mcprog.conf ] || install -c -m644 mcprog.conf /usr/local/etc/mcprog.conf

###
adapter-bitbang.o: adapter-bitbang.c adapter.h oncd.h
adapter-mpsse.o: adapter-mpsse.c adapter.h oncd.h
adapter-lpt.o: adapter-lpt.c adapter.h oncd.h
adapter-usb.o: adapter-usb.c adapter.h oncd.h
conf.o: conf.c conf.h
mcprog.o: mcprog.c target.h conf.h
target.o: target.c target.h adapter.h oncd.h
