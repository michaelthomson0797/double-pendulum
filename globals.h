#include <math.h>
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

struct Point {
  int x;
  int y;
};

struct Pendulum {
  struct Point pivot;
  struct Point bob;
  double m;
  double L;
  double theta;
  double theta_1;
  double theta_2;
};

#endif
