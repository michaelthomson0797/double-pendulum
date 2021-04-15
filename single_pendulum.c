#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "globals.h"
#include "bresenham.h"

// EDIT THESE
// Gravity
double g = -0.01;

// Damping Coefficent (set to 0 for no damping)
double b = 0.001;

// Pendulum
// Mass
double p_m = 1;
// Length
double p_L = 10;
// Initial angle
double p_theta = M_PI/2;

void print(int grid[100][100])
{

  erase();
  for (int i = 0; i < 100; i++)
  {
    for (int j = 0; j < 100; j++)
    {
      if (grid[i][j] == 1)
      {
        mvaddch(i, j, '#');
      }
    }
  }
  refresh();

}

void delay(double milli_seconds)
{
    // Storing start time
    clock_t start_time = clock();
  
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


int main()
{
  int grid[100][100] = {0};

  struct Pendulum p;

  p.pivot.x = 25;
  p.pivot.y = 25;
  p.m = p_m;
  p.L = p_L;
  p.theta = p_theta;
  p.theta_1 = 0;

  initscr();

  curs_set(0);

  while (true) {
    memset(grid, 0, sizeof(grid[0][0]) * 100 * 100);
    int x1 = round(p.L * sin(p.theta-M_PI/2) + p.pivot.x);
    int y1 = round(p.L * cos(p.theta-M_PI/2) + p.pivot.y);

    bresenham(grid, p.pivot.x, p.pivot.y, x1, y1);

    print(grid);

    p.theta_2 = -g/p.L * sin(p.theta) - p.theta_1*b;
    p.theta_1 += p.theta_2;
    p.theta += p.theta_1;

    delay(5000);
  }

  endwin();

  return 0;
}
