CC=gcc
GCC=g++
CFLAGS=
DFLAGS=-g -Og
BFLAGS=-O2
LFLAGS=
LIBS=

debug: override CFLAGS+=$(DFLAGS)
debug: all

build: override CFLAGS+=$(BFLAGS)
build: all

all: makegen

makegen: makegen.o Reader.o Crawler.o Writer.o Makefile.o
	$(GCC) $(LFLAGS) -o $@ $^ $(LIBS)

makegen.o: makegen.cc Makefile.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Reader.o: Reader.cc Reader.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Crawler.o: Crawler.cc Crawler.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Writer.o: Writer.cc Writer.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Makefile.o: Makefile.cc Makefile.h
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o makegen
