/************************************************************

Copyright (C) 1998, Lucent Technologies
All rights reserved

************************************************************/

/* Plotting functions for Sys V and BSD systems */

extern void space(int, int, int, int);
extern void cont(int, int);
extern void label(char *);
extern void linemod(char *);

void
range(int xmin, int ymin, int xmax, int ymax)
{
	space(xmin, ymin, xmax, ymax);
}

void
text(char *s)
{
	label(s);
}

void
vec(int x, int y)
{
	cont(x, y);
}

void
pen(char *s)
{
	linemod(s);
}
