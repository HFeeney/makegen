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

makegen: makegen.o Reader.o Crawler.o Writer.o MakefileStruct.o
	$(GCC) $(LFLAGS) -o $@ $^ $(LIBS)

makegen.o: makegen.cc MakefileStruct.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Reader.o: Reader.cc Reader.h MakefileStruct.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Crawler.o: Crawler.cc Crawler.h MakefileStruct.h
	$(GCC) $(CFLAGS) -c -o $@ $<

Writer.o: Writer.cc Writer.h MakefileStruct.h
	$(GCC) $(CFLAGS) -c -o $@ $<

MakefileStruct.o: MakefileStruct.cc MakefileStruct.h
	$(GCC) $(CFLAGS) -c -o $@ $<

clean:
	/bin/rm -f *.o makegen
