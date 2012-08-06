OSTYPE = $(shell uname -s)

LINUX_LIBS    = -lpthread -lresolv -lnsl -lcurl

DEFS   = -D_REENTRANT -D_POSIX_C_SOURCE -D__EXTENSIONS__ -D_POSIX_PTHREAD_SEMANTICS -D_POSIX_MAPPED_FILES -D_SVID_SOURCE -D_XOPEN_SOURCE=500


LIBS = $(LINUX_LIBS)
TESTLIBS = $(LINUX_LIBS)
TESTLIBS+= -lefence

CC     = gcc
CFLAGS = -Wall -ansi -pedantic -g3
C_CFILES = client.c proxy_rpc_clnt.c proxy_rpc_xdr.c
C_HFILES = util.h proxy_rpc.h
P_CFILES = proxy.c proxy_rpc_svc.c proxy_rpc_xdr.c
P_HFILES = proxy_rpc.h
SUNWSPRO_CC = /opt/SUNWspro/bin/cc
RPCGEN   = rpcgen
RPCGEN_FLAGS = -M -C -K -1

RPC_FILES = proxy_rpc_svc.c proxy_rpc_xdr.c proxy_rpc.h proxy_rpc_clnt.c

fetch:	fetch.c
	$(CC) -o $@ $(CFLAGS) $(DEFS) $< $(LIBS)

all: proxy client 

client: $(C_CFILES) $(C_HFILES)
	$(CC) -o $@ $(CFLAGS) $(DEFS) $(C_CFILES) $(LIBS)

proxy: $(P_CFILES) $(P_HFILES)
	$(CC) -o $@ $(CFLAGS) $(DEFS) $(P_CFILES) $(LIBS)

rpc: proxy.x
	$(RPCGEN) $(RPCGEN_FLAGS) $<

#  if you prefer independent file generation for more control
#  over file names and whether all files are generated, etc.
#	$(RPCGEN) $(RPCGEN_FLAGS) -m $< -o proxy_rpc_svc.c
#	$(RPCGEN) $(RPCGEN_FLAGS) -c $< -o proxy_rpc_xdr.c
#	$(RPCGEN) $(RPCGEN_FLAGS) -l $< -o proxy_rpc_clnt.c
#	$(RPCGEN) $(RPCGEN_FLAGS) -h $< -o proxy_rpc.h


%.h : ;

ostest:
	echo $(OSTYPE)

clean:
	rm -f simple proxy client $(RPC_FILES) *.o

# I highly suggest you do your development on Linux, but remember, if
# you're using libcurl on Solaris 8 (using the version I built),
# you'll need to add /net/hp96/davidhi/curl-sparc-sun-solaris2.8/lib
# to your LD_LIBRARY_PATH before you run the executable or else it
# will complain about not finding the curl libraries.

# export LD_LIBRARY_PATH=/net/hp96/davidhi/curl-sparc-sun-solaris2.8/lib:$LD_LIBRARY_PATH
# ./simple
