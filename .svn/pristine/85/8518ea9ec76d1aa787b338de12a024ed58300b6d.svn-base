/* Routines for drawing the graph grid and drawing lines to the graph */

#pragma once

#define GRAPH_TOP       210
#define GRAPH_LEFT       80
#define GRAPH_BOTTOM    550
#define GRAPH_RIGHT     795
#define GRAPH_BORDERW     6

#define GRAPH_YTICS       5
#define GRAPH_XTICS       6

void graph_drawgrid(int xmin, int xmax, int ymin, int ymax);

/* Draw a straight line (measurements) */
void graph_drawline(int x0, int y0, int x1, int y1);

/* Draw a quadratic curve (prediction) */
/* Factors are scaled by 1/1000. */
void graph_drawcurve(int a, int b, int c);

/* Draw a linear prediction */
void graph_drawlinear(int px, int py, int uc_per_second);
