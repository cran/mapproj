/************************************************************

Copyright (C) 1998, Lucent Technologies
All rights reserved

************************************************************/

#include "plot.h"
#include <stdio.h>
#include <string.h>

/* Plotting functions for PostScript */

static double _a,_b,_c,_d, _ox, _oy;
static double width = 0;

#define xs(_x) (_ox = _a*(_x)+_b)
#define ys(_y) (_oy = _c*(_y)+_d)

void
range(int xmin, int ymin, int xmax, int ymax)
{
	_a = 6.5*72/(xmax-xmin);
	_b = -_a*xmin + 1.0*72;
	_c = 6.5*72/(ymax-ymin);
	_d = -_c*ymin + 3.5*72;
}


/* open the plotting output */
void
erase(void)
{
	printf("%%!PS\n"
		"%%Creator: map\n"
		"%%BoundingBox: 72 252 540 720\n"
		"%%EndComments\n"
		"/co /sethsbcolor load def\n"
		"/m /moveto load def\n"
		"/s /stroke load def\n"
		"/t {gsave newpath 0 0 moveto (X) true charpath "
		"flattenpath pathbbox /charht exch def pop pop pop grestore "
		"charht 2 div sub moveto show} bind def\n"
		"/v /lineto load def\n"
		"%%EndProlog\n"
		"gsave\n"
		"/Helvetica findfont 10 scalefont setfont\n"
		"1 setlinecap\n"
		"1 setlinejoin\n"
		".5 setlinewidth\n"
		"newpath\n"
		"72 72 m\n");
}

/* close the plotting output */
void
closepl(void)
{
	printf("showpage\ngrestore\n");
}

/* make sure the page or screen is clear (on some old systems) */
void
openpl(void)
{
	printf("");
}

/* plot a point at _x,_y, which becomes current */
void
point(int _x, int _y)
{
	printf("s\n%.1f %.1f m\n",xs(_x),ys(_y));
}

/* place text, first letter at current point, which does not change */
void
text(char *_s)
{
	printf("(%s) %.1f %.1f t\n",_s,_ox,_oy);
}

/* draw line from current point to _x,_y, which becomes current */
void
vec(int _x, int _y)
{
	printf("%.1f %.1f v\n", xs(_x),ys(_y));
}

/* _x,_y becomes current point */
void
move(int _x, int _y)
{
	printf("s\n%.1f %.1f m\n", xs(_x), ys(_y));
}

struct dashpat {
	char *name;
	char *pat;
	double width;
} pattern[] = {
	{ SOLID, "[] 0", .5 },		/* pattern, minimum acceptable width */
	{ DOTTED, "[3 6] 0", 0 },
	{ DOTDASH, "[18 6 3 6] 0", .5}
};

/* specify style for drawing lines: "dotted", "solid", "dotdash" */
void
pen(char *s)
{
	int i;
	char *t;
	double w = width;
	for(i=0; i<sizeof(pattern)/sizeof(*pattern); i++)
		if(strcmp(s,pattern[i].name) == 0)
			break;
	if(i >= sizeof(pattern)/sizeof(*pattern)) {
		while((t = strchr(s, ',')))
			*t = ' ';
	} else if(width <= pattern[i].width)
		w = pattern[i].width;
	printf("s\n%.2f setlinewidth\n%s setdash\n",
		w, pattern[i].pat);
}

static struct {
	char *name;
	char *hsbcode;
} colors[] = {
	{ BLACK, "0 0 0" },
	{ RED, "0 1 1" },
	{ GREEN, ".33 1 1" },
	{ BLUE, ".67 1 1" }
};

void
color(char *s)
{
	char *t;
	int i;
	for(i=0; i<sizeof(colors)/sizeof(*colors); i++)
		if(strcmp(s, colors[i].name) == 0)
			s = colors[i].hsbcode;
	while((t = strchr(s, ',')))
		*t = ' ';
	printf("s\n%s co\n",s);
}

void
weight(double w)
{
	width = w;
}

void
comment(char *s, char *t)
{
	printf("%%%s %s\n",s,t);
}
