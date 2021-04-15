#include "globals.h"
#include "bresenham.h"
#include <stdlib.h>

int plotLineLow(int grid[100][100], int x0, int y0, int x1, int y1)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;

  if (dy < 0)
  {
    yi = -1;
    dy = -dy;
  }

  int D = (2 * dy) - dx;
  int y = y0;

  for (int x = x0; x <= x1; x++)
  {
    grid[x][y] = 1;
    if (D > 0)
    {
      y = y + yi;
      D = D + (2 * (dy - dx));
    }
    else
    {
      D = D + 2*dy;
    }
  }

  return 1;
}

int plotLineHigh(int grid[100][100], int x0, int y0, int x1, int y1)
{
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  
  if (dx < 0)
  {
    xi = -1;
    dx = -dx;
  }

  int D = (2 * dx) - dy;
  int x = x0;

  for (int y = y0; y <= y1; y++)
  {
    grid[x][y] = 1;
    if (D > 0)
    {
      x = x + xi;
      D = D + (2 * (dx - dy));
    }
    else
    {
      D = D + 2*dx;
    }
  }

  return 1;
}

int bresenham(int grid[100][100], int x0, int y0, int x1, int y1)
{
  if (abs(y1-y0) < abs(x1-x0)){
    if (x0 > x1) {
      plotLineLow(grid, x1, y1, x0, y0);
    } else {
      plotLineLow(grid, x0, y0, x1, y1);
    }
  } else {
    if (y0 > y1) {
      plotLineHigh(grid, x1, y1, x0, y0);
    } else {
      plotLineHigh(grid, x0, y0, x1, y1);
    }
  }

  return 1;
}
