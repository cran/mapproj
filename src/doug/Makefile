# /************************************************************
#
# Copyright (C) 1998, Lucent Technologies
# All rights reserved
#
# ************************************************************/

# local settings
#
# BIN		where to install map.sh ("map" command)
# LIB		where to install libmap.a (ld ... -lmap)
# MAPHOME	director of files used by map command
# PROG		"map" in unix/linux; "map.exe" in cygwin
#
CFLAGS = -O -Wall
CC=gcc
BIN = /usr/bin
LIB = /usr/lib
MAPHOME = $(LIB)/map
PROG = map

# usage
# make   	    map command compiled for PostScript output
# make PLOT=plotV   for output to SVR2 and BSD plot filters
# make PLOT=plot0   for output to v10 plot filters
# make route	    see man page route.1


PLOT=plotPS

$(PROG): map.o index.o symbol.o $(PLOT).o libmap/libmap.a
	chmod +x map.sh
	$(CC) $(CFLAGS) -o $(PROG) -DMAPDIR=$(MAPDIR) \
	    map.o index.o symbol.o $(PLOT).o \
	    libmap/libmap.a -lm 2>/dev/null || \
	$(CC) $(CFLAGS) -o $(PROG) -DMAPDIR=$(MAPDIR) \
	    map.o index.o symbol.o $(PLOT).o \
	    libmap/libmap.a -lm -lplot

map.o: map.c map.h plot.h
	$(CC) $(CFLAGS) -c $(CFLAGS) map.c

plotV.o: plotV.c plot.h
	rm -f plot*.o
	$(CC) $(CFLAGS) -c plotV.c

plotPS.o: plotPS.c plot.h
	rm -f plot*.o
	$(CC) $(CFLAGS) -c plotPS.c

plot0.o: plot0.c
	rm -f plot*.o
	$(CC) $(CFLAGS) -c plot0.c

symbol.o: symbol.c map.h

index.o: index.c map.h

route: route.o map.h libmap/libmap.a
	$(CC) $(CFLAGS) route.o libmap/libmap.a -lm -o route

libmap/libmap.a: dummy
	cd libmap; make CC=$(CC) CFLAGS="$(CFLAGS)"

dummy:
	:

ascii2map: ascii2map1 ascii2map2 ascii2map3
	chmod +x ascii2map

ascii2map1: ascii2map1.c
	$(CC) $(CFLAGS) ascii2map1.c -lm -o ascii2map1

ascii2map2: ascii2map2.c
	$(CC) $(CFLAGS) ascii2map2.c -lm -o ascii2map2

ascii2map3:	ascii2map3.c
	$(CC) $(CFLAGS) ascii2map3.c -o ascii2map3

map2ascii: map2ascii.c
	$(CC) $(CFLAGS) map2ascii.c -lm -o map2ascii

install: $(PROG)
	-strip $(PROG)
	test -d $(MAPHOME) || mkdir $(MAPHOME)
	test -d $(MAPHOME)/bin || mkdir $(MAPHOME)/bin
	test -d $(MAPHOME)/lib || mkdir $(MAPHOME)/lib
	cp $(PROG) $(MAPHOME)/bin
	cp map.sh $(BIN)/map
	chmod +x $(BIN)/map
	test -f $(MAPHOME)/lib/world || cp mapdata/* $(MAPHOME)/lib

installall: install route libmap/libmap.a
	strip route
	cp route $(BIN)
	cp libmap/libmap.a $(LIB)

clean:
	rm -f $(PROG) route *.o new.results map.tar*
	cd libmap; make clean

quicktest:
	make PLOT=plotPS
	MAPPROG=./$(PROG) MAPDIR=./mapdata ./map.sh mercator -l 0 10 0 10 -g -b >new.results
	:
	: If any "diff" output follows, it should show only roundoff differences.
	diff test.results new.results

map.tar.gz: dummy
	cd doc; make
	for i in map.sh Makefile; \
		do mv $$i $$i.save; cp $$i.template $$i; \
		done
	tar cf map.tar \
		README Makefile map.sh test.results \
		map.h map.c index.c symbol.c \
		plot.h iplot.h plotPS.c plotV.c plot0.c \
		route.c ascii2map ascii2map[123].c \
		libmap/Makefile libmap/*.c \
		mapdata/world* mapdata/states* mapdata/counties* \
		doc/*
	for i in map.sh Makefile; \
		do mv $$i.save $$i; \
		done
	rm -f map.tar.gz
	gzip map.tar
	echo >/dev/null
