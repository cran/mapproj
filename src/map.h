/* Copyright (C) 2003, Lucent Technologies Inc. and others. 
 * All Rights Reserved. */
/* RSB #pragma	lib	"/sys/src/cmd/map/libmap/libmap.a$O"
#pragma	src	"/sys/src/cmd/map/libmap"*/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifndef PI
#define PI	3.1415926535897932384626433832795028841971693993751
#endif

#define TWOPI (2*PI)
#define RAD (PI/180)
double	hypot(double, double);	/* sqrt(a*a+b*b) */
double	tan(double);		/* not in K&R library */

#define ECC .08227185422	/* eccentricity of earth */
#define EC2 .006768657997

#define FUZZ .0001
#define UNUSED 0.0		/* a dummy double parameter */

struct coord {
	double l;	/* lat or lon in radians*/
	double s;	/* sin */
	double c;	/* cos */
};
struct place {
	struct coord nlat;
	struct coord wlon;
};

typedef int (*proj)(struct place *, double *, double *);

struct pindex {	/* RSB */	/* index of known projections */
	char *name;	/* name of projection */
	proj (*prog)(double, double);
			/* pointer to projection function */
	int npar;	/* number of params */
	int (*cut)(struct place *, struct place *, double *);
			/* function that handles cuts--eg longitude 180 */
	int poles;	/*1 S pole is a line, 2 N pole is, 3 both*/
	int spheroid;	/* poles must be at 90 deg if nonzero */
	int (*limb)(double *lat, double *lon, double resolution);
			/* get next place on limb */
			/* return -1 if done, 0 at gap, else 1 */
};


proj	aitoff(double, double);
proj	albers(double, double);
int	Xazequalarea(struct place *, double *, double *);
proj	azequalarea(double, double);
int	Xazequidistant(struct place *, double *, double *);
proj	azequidistant(double, double);
proj	bicentric(double, double);
proj	bonne(double, double);
proj	conic(double, double);
proj	cylequalarea(double, double);
int	Xcylindrical(struct place *, double *, double *);
proj	cylindrical(double, double);
proj	elliptic(double, double);
proj	eisenlohr(double, double); /* RSB */
proj	fisheye(double, double);
proj	gall(double, double);
proj	gilbert(double, double);
proj	globular(double, double);
proj	gnomonic(double, double);
/* AD int	guycut(struct place *, struct place *, double *); */
int	Xguyou(struct place *, double *, double *);
proj	guyou(double,double);
proj	harrison(double, double);
/* AD int	hexcut(struct place *, struct place *, double *); */
proj	map_hex(double, double);
proj	homing(double, double);
int	hlimb(double*, double*, double resolution);
proj	lagrange(double, double);
proj	lambert(double, double);
proj	laue(double, double);
proj	lune(double, double);
proj	loxodromic(double);	/* not in library */
proj	mecca(double, double);
int	mlimb(double*, double*, double resolution);
proj	mercator(double, double);
proj	mollweide(double, double);
proj	newyorker(double, double);
proj	ortelius(double, double);	/* not in library */
int	Xorthographic(struct place *place, double *x, double *y);
proj	orthographic(double, double);
int	olimb(double*, double*, double);
proj	map_perspective(double, double);
int	plimb(double*, double*, double resolution);
int	Xpolyconic(struct place *, double *, double *);
proj	polyconic(double, double);
proj	rectangular(double, double);
proj	simpleconic(double, double);
int	Xsinusoidal(struct place *, double *, double *);
proj	sinusoidal(double, double);
proj	sp_albers(double, double);
proj	sp_mercator(double, double);
proj	square(double, double);
int	Xstereographic(struct place *, double *, double *);
proj	stereographic(double, double);
int	Xtetra(struct place *, double *, double *);
/* AD int	tetracut(struct place *, struct place *, double *); */
proj	tetra(double, double);
proj	trapezoidal(double, double);
proj	vandergrinten(double, double);
proj	wreath(double, double);	/* not in library */

void	findxy(double, double *, double *);
void	albscale(double, double, double, double);
void	invalb(double, double, double *, double *);

void	cdiv(double, double, double, double, double *, double *);
void	cmul(double, double, double, double, double *, double *);
/* RSB void	cpow(double, double, double *, double *, double);*/
void	map_cpow(double, double, double *, double *, double);
void	csq(double, double, double *, double *);
/* RSB void	csqrt(double, double, double *, double *);*/
void	map_csqrt(double, double, double *, double *);
void	ccubrt(double, double, double *, double *);
double	cubrt(double);
int	elco2(double, double, double, double, double, double *, double *);
void	cdiv2(double, double, double, double, double *, double *);
void	csqr(double, double, double *, double *);

void	orient(double, double, double);
void	latlon(double, double, struct place *);
void	deg2rad(double, struct coord *);
/* RSB void	sincos(struct coord *);*/
void	trig(struct coord *);
void	normalize(struct place *);
void	invert(struct place *);
void	norm(struct place *, struct place *, struct coord *);
/* void	printp(struct place *); */
void	copyplace(struct place *, struct place *);

/* AD int	picut(struct place *, struct place *, double *); */
/* AD int	ckcut(struct place *, struct place *, double); */
double	reduce(double);

/* RSB void	getsyms(char *);
int	putsym(struct place *, char *, double, int);
void	filerror(char *s, char *f);
void	error(char *s);
int	doproj(struct place *, int *, int *);
int	cpoint(int, int, int);
int	plotpt(struct place *, int);
int	nocut(struct place *, struct place *, double *);*/

extern int (*projection)(struct place *, double *, double *);
