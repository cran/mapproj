#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

/* convert an ascii file of lat-lon data to map(5) format,

   input: sequence of segments, each of which comprises
		integer count
		sequence of north-lat west-lon pairs

   first phase (mapfile1.c): make intermediate file
   intermediate data layout, one line per point:
	patchlat (-9 to 8)	10-degree patch in which 
	patchlon (-18 to 17)	    segment starts
	point number		sequential, with gap between segs
	scaled lat		units of .0001 radian (6.4km, 4mi)
	scaled lon		    or .00001 radian (option -f)

   interphase: sort the intermediate file by patch and point number

   second phase (mapfile2.c): convert to map(5) binary

   warning: incomplete error checking.
*/

/* SECOND PHASE */

#define N 32000		/* max points per segment (must fit in signed short) */


void error(char*);
void putshort(int);
void output(int);

int fflag = 0;

int plat0, plon0;
int ilat[N+1], ilon[N+1]; 

int main(int argc, char**argv)
{
	int n = 0;
	int point;
	int point0 = -1;
	int plat, plon;
	fflag = argc>1 && strcmp(argv[1],"-f")==0;
	plat0 = plon0 = INT_MIN;
	while(scanf("%d %d %d %d %d",
	      &plat, &plon ,&point, ilat+n, ilon+n) == 5) {
		if(point != point0+1) {
			output(n);
			ilat[0] = ilat[n];
			ilon[0] = ilon[n];
			n = 1;
		} else
			n++;
		point0 = point;
		plat0 = plat;
		plon0 = plon;
	}
	output(n);
	return 0;		
}

void output(int n)
{
	int i;
	if(n == 0)
		return;
	putchar(plat0&0xff);
	putchar(plon0&0xff);
	if(fflag) {
		int ilat0 = ilat[0]/10;
		int ilon0 = ilon[0]/10;
		putshort(-n);
		putshort(ilat0);
		putshort(ilon0);
		putchar(ilat[0]-ilat0*10);
		putchar(ilon[0]-ilon0*10);
		for(i=1; i<n; i++) {
			putchar(ilat[i]-ilat[i-1]);
			putchar(ilon[i]-ilon[i-1]);
		}
	} else {
		putshort(n);
		for(i=0; i<n; i++) {
			putshort(ilat[i]);
			putshort(ilon[i]);
		}
	}
}

void error(char *s) 
{
	fprintf(stderr,"ascii2map2: %s\n", s);
	exit(1);
}

void putshort(int x)
{
	putchar(x&0xff);
	putchar(x>>8&0xff);
}
