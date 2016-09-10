
#include "tempgraph.h"
#include <gfx.h>
#include <stdio.h>

static int g_ymin;
static int g_ymax;
static int g_xmin;
static int g_xmax;

// Get the y pixel coordinate from a value on the y axis
int graph_gety(int yval)
{
    return GRAPH_BOTTOM + (GRAPH_TOP - GRAPH_BOTTOM) * (yval - g_ymin) / (g_ymax - g_ymin);
}

// Get the x pixel coordinate from a value on the x axis
int graph_getx(int xval)
{
    return GRAPH_LEFT + (GRAPH_RIGHT - GRAPH_LEFT) * (xval - g_xmin) / (g_xmax - g_xmin);
}

// Round the y tick interval to a nice value (1, 5, 10, 20, 30, 40, 50)
static int round_yticks(int tick)
{
    if (tick <= 1000)  return  1000;
    if (tick <= 5000)  return  5000;
    if (tick <= 10000) return 10000;
    if (tick <= 20000) return 20000;
    if (tick <= 30000) return 30000;
    if (tick <= 40000) return 40000;
    
    return 50000;
}

// Round the x tick interval to a nice value (1 min, 5 min, 10 min, etc.)
static int round_xticks(int tick)
{
    if (tick <= 60) return 60;
    if (tick <= 120) return 120;
    if (tick <= 300) return 300;
    if (tick <= 600) return 600;
    if (tick <= 900) return 900;
    if (tick <= 1800) return 1800;
    if (tick <= 3600) return 3600;
    if (tick <= 7200) return 7200;
    
    return 14400;
}

void graph_drawgrid(int xmin, int xmax, int ymin, int ymax)
{
    // Store the graph bounds for later use
    g_ymin = ymin;
    g_ymax = ymax;
    g_xmin = xmin;
    g_xmax = xmax;
    
    // Figure out the tick intervals
    int xtick = round_xticks((xmax - xmin) / GRAPH_XTICS);
    int ytick = round_yticks((ymax - ymin) / GRAPH_YTICS);
    
    font_t mediumfont = gdispOpenFont("mediumfont");
    
    // Draw the Y axis label
    gdispDrawString(GRAPH_LEFT - 60, GRAPH_TOP, "°C", mediumfont, 0);
    
    // Draw Y axis and ticks
    gdispFillArea(GRAPH_LEFT, GRAPH_TOP, GRAPH_BORDERW, GRAPH_BOTTOM - GRAPH_TOP, 0);
    
    for (int y = ymin - ymin % ytick; y <= ymax; y += ytick)
    {
        if (y < ymin) continue;
        
        int ypx = graph_gety(y);
        gdispDrawLine(GRAPH_LEFT, ypx, GRAPH_RIGHT, ypx, 0);
        
        if (ypx > GRAPH_TOP + 50)
        {
            char buf[8];
            snprintf(buf, sizeof(buf), "%d", y / 1000);
            gdispDrawStringBox(0, ypx - 30, GRAPH_LEFT - 5, 60, buf, mediumfont, 0, justifyRight);
        }
    }
    
    // Draw X axis and ticks
    gdispFillArea(GRAPH_LEFT, GRAPH_BOTTOM - GRAPH_BORDERW + 1, GRAPH_RIGHT - GRAPH_LEFT, 6, 0);
    
    for (int x = xmin - xmin % ytick; x <= xmax; x += xtick)
    {
        if (x < xmin) continue;
        
        int xpx = graph_getx(x);
        gdispDrawLine(xpx, GRAPH_BOTTOM, xpx, GRAPH_TOP, 0);
        
        if (xpx > GRAPH_LEFT + 30 && xpx <= GRAPH_RIGHT - 60)
        {
            char buf[8];
            snprintf(buf, sizeof(buf), "%d:%02d", x / 3600, (x % 3600) / 60);
            gdispDrawStringBox(xpx - 50, GRAPH_BOTTOM, 100, 60, buf, mediumfont, 0, justifyCenter);
        }
    }
}

static bool graph_contains(int x, int y)
{
    return (x >= g_xmin && x <= g_xmax && y >= g_ymin && y <= g_ymax);
}

void graph_drawline(int x0, int y0, int x1, int y1)
{
    if (graph_contains(x0, y0) && graph_contains(x1, y1))
    {
        gdispDrawThickLine(graph_getx(x0), graph_gety(y0),
                           graph_getx(x1), graph_gety(y1),
                           Black, 4, true);
    }
}

void graph_drawcurve(int a, int b, int c)
{
    int step = (g_xmax - g_xmin) / 100;
    for (int x = g_xmin; x < g_xmax; x += step)
    {
        int x0 = x;
        int x1 = x + step / 2;
        int y0 = (a * x0 * x0 + b * x0 + c) / 1000;
        int y1 = (a * x1 * x1 + b * x1 + c) / 1000;
        
        if (graph_contains(x0, y0) && graph_contains(x1, y1))
        {
            gdispDrawLine(graph_getx(x0), graph_gety(y0),
                        graph_getx(x1), graph_gety(y1),
                        Black);
        }
    }
}

void graph_drawlinear(int px, int py, int uc_per_second)
{
    int step = (g_xmax - g_xmin) / 100;
    for (int x = px; x < g_xmax; x += step)
    {
        int x0 = x;
        int x1 = x + step / 2;
        int y0 = py + (x0 - px) * uc_per_second / 1000;
        int y1 = py + (x1 - px) * uc_per_second / 1000;
        
        if (graph_contains(x0, y0) && graph_contains(x1, y1))
        {
            gdispDrawLine(graph_getx(x0), graph_gety(y0),
                        graph_getx(x1), graph_gety(y1),
                        Black);
        }
    }
}
