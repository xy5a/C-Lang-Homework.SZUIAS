#include "math.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdlib.h"

double prof_demand = 0.01;
double prof_fixed = 0.03;
double prof_fixed_twice = 0.02;

bool _is_leap(int year) {
  return (!(year % 4) && (year % 100)) || !(year % 400);
}

void is_leap(int argc, char **argv) {

  printf("%d %s a leap year\n", atoi(argv[1]),
         _is_leap(atoi(argv[1])) ? "is" : "is not");
}

double _calc_func(double x) {
  const double a = 1, b = 5;
  return x >= -10. ? -a * (b + x) : 3. / ((pow(a, 3) + pow(x, 3)) * b);
}

void calc_func(int argc, char **argv) {

  printf("calc_func(%.2f) = %10f\n", atof(argv[1]), _calc_func(atof(argv[1])));
}

double _calc_prof_once(double p, double r) { return p * (1 + r); }

double _calc_prof_twice(double p, double r) {
  return _calc_prof_once(_calc_prof_once(p, r / 2), r / 2);
}
