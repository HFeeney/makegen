CC=gcc
GCC=g++
CFLAGS=
DFLAGS=-g -Og
BFLAGS=-O2
LFLAGS=
LIBS=

# setup
debug: override CFLAGS+=$(DFLAGS)
debug: all

build: override CFLAGS+=$(BFLAGS)
build: all

all: makegen

makegen: makegen.o Writer.o
	$(GCC) $(LFLAGS) -o $@ $^ $(LIBS)

makegen.o: makegen.cc Makefile.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Writer.o: Writer.cc Writer.h
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f makegen *.o