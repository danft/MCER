#ifndef UTILS_H 
#define UTILS_H 

#include <cmath>
#include <vector>
#include <complex>

using namespace std;

const double pi = acos(-1);

struct Point{
	double x = 0;
	double y = 0;
	Point(double x, double y): x(x), y(y) {}
	Point(){}

	double dist(const Point &p) const;
};

double triangle_area(const Point &p1, const Point &p2, const Point &p3);

double todouble(string num);
double eval_ellipse(double a, double b, double theta, double xc, double yc, double x, double y);
bool is_colinear(double x1, double x2, double y1, double y2);
void print_complex(double re, double im);
complex<double> poly_eval(vector<complex<double>> pol, complex<double> z);
vector<vector<double>> get_inv_2(vector<vector<double>> A);
Point get_circumcenter(double x1, double x2, double y1, double y2);

#endif
