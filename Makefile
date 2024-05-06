CC=gcc
GCC=g++
CFLAGS=--std=c++20
DFLAGS=-g -Og
BFLAGS=-O2
LFLAGS=
LIBS=-lboost_filesystem

debug: override CFLAGS+=$(DFLAGS)
debug: all

build: override CFLAGS+=$(BFLAGS)
build: all

all: makegen

makegen: makegen.o Crawler.o MakefileStruct.o Reader.o Writer.o
	$(GCC) $(LFLAGS) -o $@ $^ $(LIBS)

Crawler.o: Crawler.cc Crawler.h MakefileStruct.h Filename.h
	$(GCC) $(CFLAGS) -c -o $@ $<

MakefileStruct.o: MakefileStruct.cc MakefileStruct.h Filename.h
	$(GCC) $(CFLAGS) -c -o $@ $<

makegen.o: makegen.cc Reader.h MakefileStruct.h Filename.h Crawler.h Writer.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Reader.o: Reader.cc Reader.h MakefileStruct.h Filename.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Writer.o: Writer.cc Writer.h MakefileStruct.h Filename.h io_error.h
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o makegen
