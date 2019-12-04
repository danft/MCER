#ifndef UTILS_H 
#define UTILS_H 

#include <cmath>
#include <vector>
#include <complex>

using namespace std;

const double pi = acos(-1);

struct Point{
	double x; 
	double y;
	Point(double x, double y): x(x), y(y) {}
	Point(){}
};

bool is_colinear(double x1, double x2, double y1, double y2);
void print_complex(double re, double im);
complex<double> poly_eval(vector<complex<double>> pol, complex<double> z);
vector<vector<double>> get_inv_2(vector<vector<double>> A);
Point get_circumcenter(double x1, double x2, double y1, double y2);

#endif
