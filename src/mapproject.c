#include "R.h"
#include "map.h"

#define MIN(a,b)	(a)<(b)?(a):(b)
#define MAX(a,b)	(a)>(b)?(a):(b)
#define ABS(x)		((x)<0?-(x):(x))
#define RAD2DEG(x)	((x)*180/PI)
#define DEG2RAD(x)	((x)*PI/180)

/* must be consistent with map.h in maps library */
#define XMIN		0
#define XMAX		1
#define YMIN		2
#define YMAX		3

static int (*projfun)(struct place*, double*, double*);

struct index {
	char *name;
	proj (*prog)(double, double);
	int npar;
} mapindex[] = {
	{"mercator", mercator, 0},
	{"cylindrical", cylindrical, 0},
	{"cylequalarea", cylequalarea, 1},
	{"rectangular", rectangular, 1},
	{"trapezoidal", trapezoidal, 2},
	{"lune",lune,2},
	{"gall", gall, 1},
	{"sinusoidal", sinusoidal, 0},
	{"mollweide", mollweide, 0},
	{"gilbert", gilbert, 0},
	{"azequidistant", azequidistant, 0},
	{"azequalarea", azequalarea, 0},
	{"gnomonic", gnomonic, 0},
	{"perspective", map_perspective, 1},
	{"harrison", harrison, 2},
	{"orthographic", orthographic, 0},
	{"stereographic", stereographic, 0},
	{"laue", laue, 0},
	{"fisheye", fisheye, 1},
	{"newyorker", newyorker, 1},
	{"conic", conic, 1},
	{"lambert", lambert, 2},
	{"albers", albers, 2},
	{"bonne", bonne, 1},
	{"polyconic", polyconic, 0},
	{"aitoff", aitoff, 0},
	{"globular", globular, 0},
	{"vandergrinten", vandergrinten, 0},
	{"eisenlohr", eisenlohr, 0},
	{"guyou",guyou,0},
	{"square",square,0},
	{"tetra",tetra,0},
	{"hex",map_hex,0},
	{"lagrange",lagrange,0},
	{"bicentric", bicentric, 1},
	{"elliptic", elliptic, 1},
	{"mecca", mecca, 1},
	{"simpleconic", simpleconic, 2},
	{"homing", homing, 1},
	{"sp_mercator", sp_mercator, 0},
	{"sp_albers", sp_albers, 2},
	{NULL,NULL,0},
};

void setproj(char **name, double par[], int *n, double o[], char **error)
{
  struct index *i, *theproj = 0;
  static char errbuf[200];

  *error = "";
  if(**name == 0) {
    *error = "Null projection specified";
    return;
  }
  for(i = mapindex; i->name != 0; i++) {
    if(strncmp(*name, i->name, strlen(*name)) == 0) {
      if(theproj) {
	sprintf(errbuf, "Ambiguous projection specified: %s or %s?", theproj->name, i->name);
	*error = errbuf;
	return;
      }
      if(*n != i->npar) {
	sprintf(errbuf, "%s projection requires %d parameter%s", i->name, i->npar, i->npar>1?"s":"");
	*error = errbuf;
	return;
      }
      if(strcmp(i->name, "bicentric") == 0 ||
	 strcmp(i->name, "elliptic") == 0)
	par[0] = -par[0];
      switch(*n) {
      /* AD: all functions now take 2 arguments */
      case 0: projfun = (i->prog)(UNUSED, UNUSED); break;
      case 1: projfun = (i->prog)(par[0], UNUSED); break;
      case 2: projfun = (i->prog)(par[0], par[1]); break;
      }
      theproj = i;
    }
  }
  if(theproj == 0) {
    sprintf(errbuf, "Unknown projection: %s", *name);
    *error = errbuf;
    return;
  }
  orient(o[0], -o[1], -o[2]);
}

static int project(double lon, double lat, double *x, double *y)
{
  struct place p;

  if(projfun == 0) {
    *x = lon;
    *y = lat;
    return(1);
  }
  lon = DEG2RAD(lon);
  lat = DEG2RAD(lat);
  p.wlon.l = -lon; p.wlon.s = sin(-lon); p.wlon.c = cos(-lon);
  p.nlat.l = lat; p.nlat.s = sin(lat); p.nlat.c = cos(lat);
  normalize(&p);
  return((*projfun)(&p, x, y));
}

void doproj(double lon[], double lat[], int *n, double range[], int *error)
{
  int i, ok;
  double x, y;

  *error = 0;
  range[XMIN] = range[YMIN] = FLT_MAX;
  range[XMAX] = range[YMAX] = -FLT_MAX;
  for(i = 0; i < *n; i++, lon++, lat++) {
    if(ISNA(*lon) || ISNA(*lat))
      continue;
    ok = 1 == project(*lon, *lat, &x, &y);
    if(!ok || ABS(x) > FLT_MAX || ABS(y) > FLT_MAX) {
      *error = 1;
      *lon = NA_REAL;
      *lat = NA_REAL;
    } else {
      *lon = x;
      *lat = y;
      range[XMIN] = MIN(range[XMIN], x);
      range[XMAX] = MAX(range[XMAX], x);
      range[YMIN] = MIN(range[YMIN], y);
      range[YMAX] = MAX(range[YMAX], y);
    }
  }
}

