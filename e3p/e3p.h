#ifndef E3P_H
#define E3P_H

#include <vector>

#include "../utils.h"

using namespace std;

vector<pair<double, Point>> e3p(double a, double b, double x1, double x2, double y1, double y2);
vector<pair<double, Point>> e3p(double a, double b, double x0, double x1, double x2, double y0, double y1, double y2);

#endif
