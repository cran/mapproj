/************************************************************

Copyright (C) 1998, Lucent Technologies
All rights reserved

************************************************************/

/* Plotting functions */

/* open the plotting output */
extern void openpl(void);

/* close the plotting output */
extern void closepl(void);

/* make sure the page or screen is clear */
extern void erase(void);

/* plot a point at x,y which becomes current */
extern void point(int x, int y);

/* coordinates to be assigned to lower left and upper right
   corners of (square) plotting area */
extern void range(int xmin, int ymin, int xmax, int ymax);

/* place text, first letter at current point, which does not change */
extern void text(char *);

/* draw line from current point to x,y which becomes current */
extern void vec(int x, int y);

/* x,y becomes current point */
extern void move(int x, int y);

/* specify style for drawing lines */

#define SOLID "solid"
#define DOTTED "dotted"
#define DOTDASH "dotdash"

extern void pen(char *);

#define BLACK "black"
#define RED "red"
#define GREEN "green"
#define BLUE "blue"

extern void color(char *);

extern void weight(double);

extern void comment(char *, char *);

