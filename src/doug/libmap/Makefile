
# .o's ordered for a nonrandom library
OBJ= aitoff.o albers.o azequalarea.o elliptic.o azequidist.o  \
bicentric.o bonne.o conic.o cylequalarea.o cylindrical.o eisenlohr.o fisheye.o \
gall.o gilbert.o guyou.o harrison.o hex.o homing.o lagrange.o lambert.o \
laue.o lune.o mercator.o mollweide.o newyorker.o polyconic.o simpleconic.o \
sinusoidal.o tetra.o perspective.o orthographic.o trapezoidal.o \
rectangular.o twocirc.o cuts.o ccubrt.o cubrt.o elco2.o complex.o zcoord.o 

# ignore error on systems without ranlib

libmap.a: ../map.h $(OBJ)
	ar cr libmap.a $(OBJ)
	ranlib libmap.a 2>/dev/null || true

clean:
	rm -f *.o libmap.a

.SUFFIXES.: .c .o
.c.o:
	$(CC) $(CFLAGS) -I.. -c $*.c
