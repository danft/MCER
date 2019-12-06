#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include <complex>

#include "roots.h"
#include "e3p.h"
#include "eig.h"
#include "poly_function.h"

using namespace std;

Point tr(double theta, double q, double x, double y) {
	return Point(
			q * (x * cos(theta) + y * sin(theta)),
			-x * sin(theta) + y * cos(theta));
}

Point tri(double theta, double q, double x, double y) {
	x /= q;
	return Point(
			x * cos(-theta) + y * sin(-theta),
			-x * sin(-theta) + y * cos(-theta));
}


Point get_center_from_angle(double theta, double a, double b, double x1, double x2, double y1, double y2) {
	Point P1 = tr(theta, b/a, x1, y1);
	Point P2 = tr(theta, b/a, x2, y2);

	Point center = get_circumcenter(P1.x, P2.x, P1.y, P2.y);

	return tri(theta, b/a, center.x, center.y); 
}

vector<complex<double>> e3p_get_polynomial(double a, double b, double x1, double x2, double y1, double y2) {

	vector<double> p_re = poly_re(a, b, x1, x2, y1, y2);
	vector<double> p_im = poly_im(a, b, x1, x2, y1, y2);

	vector<complex<double>> pol;

	for (int j = 0; j<p_re.size(); j++)
		pol.push_back(complex<double>(p_re[j], p_im[j]));

	return pol;
}

vector<pair<double, Point>> e3p(double a, double b, double x0, double x1, double x2, double y0, double y1, double y2) {
	vector<pair<double, Point>> ret = e3p(a, b, x1-x0, x2-x0, y1-y0, y2-y0);

	for (int j = 0; j<ret.size(); j++) 
	{
		ret[j].second.x += x0;
		ret[j].second.y += y0;
	}

	return ret;
}	

vector<pair<double, Point>> e3p(double a, double b, double x1, double x2, double y1, double y2) {
	if (is_colinear(x1, x2, y1, y2))
	{
		return vector<pair<double, Point>>();
	}

	// Circle case
	if (abs(a - b) < 1e-15)
	{
		Point c = get_circumcenter(x1, x2, y1, y2);

		//return vector<pair<double, Point>>({pair<double, Point>(0, c)});
		return {pair<double, Point>(0, c)};
	}

	vector<complex<double>> pcoef = e3p_get_polynomial(a, b, x1, x2, y1, y2);

	vector<complex<double>> pol_roots = roots(pcoef);

	vector<pair<double, Point>> ret;

	for (auto r : pol_roots)
		if (abs(abs(r) - 1) < 1e-13)
		{
			/*The polynomial is reduced using y=x^2*/
			double theta = arg(r)/2;
			Point cntr = get_center_from_angle(theta, a, b, x1, x2, y1, y2);
			ret.push_back(pair<double, Point>(theta, cntr));
		}

	return ret;
}

