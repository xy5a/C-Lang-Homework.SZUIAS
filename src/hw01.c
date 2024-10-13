#include "math.h"
#include "stdbool.h"

bool is_leap(int year) {
  return (!(year % 4) && (year % 100)) || !(year % 400);
}

double calc_func(double x) {
  const double a = 1, b = 5;
  return x >= -10. ? -a * (b + x) : 3. / ((pow(a, 3) + pow(x, 3)) * b);
}

double calc_prof_once(double p, double r) { return p * (1 + r); }

double calc_prof_twice(double p, double r) {
  return calc_prof_once(calc_prof_once(p, r / 2), r / 2);
}
