#include <ncurses.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "globals.h"
#include "bresenham.h"

// EDIT THESE
// Gravity
double g = -0.01;

// Damping Coefficent (set to 0 for no damping)
double b = 0.001;

// Pendulum 1
// Mass
double p1_m = 1;
// Length
double p1_L = 10;
// Initial angle
double p1_theta = M_PI/2;

// Pendulum 2
// Mass
double p2_m = 1;
// Length
double p2_L = 10;
// Initial angle
double p2_theta = M_PI/4;

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

  struct Pendulum p1;
  struct Pendulum p2;

  p1.pivot.x = 25;
  p1.pivot.y = 50;
  p1.m = p1_m;
  p1.L = p1_L;
  p1.theta = p1_theta;
  p1.theta_1 = 0;
  p1.bob.x = round(p1.L * sin(p1.theta-M_PI/2) + p1.pivot.x);
  p1.bob.y = round(p1.L * cos(p1.theta-M_PI/2) + p1.pivot.y);

  p2.pivot.x = p1.bob.x;
  p2.pivot.y = p1.bob.y;
  p2.m = p2_m;
  p2.L = p2_L;
  p2.theta = p2_theta;
  p2.theta_1 = 0;
  p2.bob.x = round(p2.L * sin(p2.theta-M_PI/2) + p2.pivot.x);
  p2.bob.y = round(p2.L * cos(p2.theta-M_PI/2) + p2.pivot.y);

  initscr();

  curs_set(0);

  while (true) {
    memset(grid, 0, sizeof(grid[0][0]) * 100 * 100);

    bresenham(grid, p1.pivot.x, p1.pivot.y, p1.bob.x, p1.bob.y);
    bresenham(grid, p2.pivot.x, p2.pivot.y, p2.bob.x, p2.bob.y);

    print(grid);

    p1.theta_2 = (-g*(2*p1.m+p2.m)*sin(p1.theta) - p2.m*g*sin(p1.theta - 2*p2.theta) - 2*sin(p1.theta - p2.theta)*p2.m*(pow(p2.theta_1,2)*p2.L + pow(p1.theta_1,2)*p1.L*cos(p1.theta - p2.theta)))/(p1.L*(2*p1.m + p2.m - p2.m*cos(2*p1.theta - 2*p2.theta)));

    p1.theta_2 -= p1.theta_1*b;

    p2.theta_2 = (2*sin(p1.theta-p2.theta)*(pow(p1.theta_1, 2)*p1.L*(p1.m + p2.m) + g*(p1.m + p2.m)*cos(p1.theta) + pow(p2.theta_1,2)*p2.L*p2.m*cos(p1.theta-p2.theta)))/(p2.L*(2*p1.m + p2.m - p2.m*cos(2*p1.theta - 2*p2.theta)));

    p2.theta_2 -= p2.theta_1*b;

    p1.theta_1 += p1.theta_2;
    p1.theta += p1.theta_1;
    p1.bob.x = round(p1.L * sin(p1.theta-M_PI/2) + p1.pivot.x);
    p1.bob.y = round(p1.L * cos(p1.theta-M_PI/2) + p1.pivot.y);

    p2.pivot.x = p1.bob.x;
    p2.pivot.y = p1.bob.y;
    p2.theta_1 += p2.theta_2;
    p2.theta += p2.theta_1;
    p2.bob.x = round(p2.L * sin(p2.theta-M_PI/2) + p2.pivot.x);
    p2.bob.y = round(p2.L * cos(p2.theta-M_PI/2) + p2.pivot.y);

    delay(6000);
  }

  endwin();

  return 0;
}
