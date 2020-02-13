#include <cmath>
#include <vector>

#include "../utils.h"
#include "e2p.h"

using namespace std;

Point rot(Point p, double theta) {
	return Point(p.x * cos(theta) - p.y * sin(theta),
			p.x * sin(theta) + p.y * cos(theta));
}

double distsq(vector<double> &X, vector<double> &Y) {
	return pow(X[0]-X[1], 2) + pow(Y[0]-Y[1], 2);
}


vector<pair<double, Point>> e2p(double a, double b, double x1, double x2, double y1, double y2) {
	double theta = 0;
	auto ret = vector<pair<double, Point>>();

	if (x1 == x2) 
		theta = pi/2;
	else 
		theta = atan((y2-y1)/(x2-x1));

	vector<double> X = vector<double>({x1, x2});
	vector<double> Y = vector<double>({y1, y2});
	for (int i = 0; i<X.size(); i++)
	{
		Point p = rot(Point(X[i], Y[i]), -theta);
		X[i] = p.x;
		Y[i] = p.y;
	}

	double m = (Y[1]-Y[0])/(X[1]-X[0]);

	double D = distsq(X, Y);
	double A = 4 * a*a * b*b + 4 * a * a * b*b * m * m;
	double B = a * a * m * m + b*b;


	if (B * A - D * B*B < 0)
		return ret;

	double c = sqrt((B*A - D * B*B) / A);

	for (int i = 0; i<2; i++) {
		x1 = (-a*a*m*c - a*b*sqrt(a*a*m*m + b*b - c*c)) / (a*a*m*m + b*b);
		x2 = (-a*a*m*c + a*b*sqrt(a*a*m*m + b*b - c*c)) / (a*a*m*m + b*b);

		if (x1 > x2)
			swap(x1, x2);

		y2 = x2 * m + c;
		y1 = x1 * m + c;

		double xc, yc;

		if (X[0] < X[1]) {
			xc = -x1 + X[0];
			yc = -y1 + Y[0];
		}
		else {
			xc = -x2 + X[0];
			yc = -y2 + Y[0];
		}

		Point center = rot(Point(xc, yc), theta);

		ret.push_back(pair<double, Point>(theta, center));
		c *= -1;
	}

	return ret;
}
