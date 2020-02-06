#include <vector>
#include <complex>
#include <iostream>

#include "utils.h"

using namespace std;

double todouble(string num) {
	double ret = 0, ax, bx;

	int epos = num.find('e');

	string a = num.substr(0, epos);
	string b = num.substr(epos+1, num.size() - epos - 1);

	if (epos == string::npos)
		b = "";

	stringstream astream = stringstream(a);
	stringstream bstream = stringstream(b);

	astream >> ax;
	
	if (b.size() > 0)
		bstream >> bx;
	else
		bx = 0;

	return ax * pow(10, bx);
}

double eval_ellipse(double a, double b, double theta, double xc, double yc, double x, double y) {
	double X = xc-x, Y = yc-y;
	double Aa = (X * cos(theta) + Y * sin(theta)) / a;
	double Bb = (X * sin(theta) - Y * cos(theta)) / b;

	return Aa*Aa + Bb*Bb;
	//return pow(X * cos(theta) + Y * sin(theta), 2)/pow(a, 2) + pow(X * sin(theta) - Y * cos(theta), 2)/pow(b, 2);
}



bool is_colinear(double x1, double x2, double y1, double y2) {
	return abs(x1 * y2 - x2 * y1) < 1e-15;
}

void print_complex(double re, double im) {
	cout << re;
	if (im > 0)
		cout << '+';
	cout << im << 'i';
}

complex<double> poly_eval(vector<complex<double>> pol, complex<double> z) {
	complex<double> ret = 0;
	auto zpot = complex<double>(1, 0);

	for (int j = 0; j< pol.size(); j++) {
		ret += pol[j] * zpot;
		zpot *= z;
	}
	
	return ret;
}

vector<vector<double>> get_inv_2(vector<vector<double>> A) {
	auto Ainv = vector<vector<double>>(2, vector<double>(2));
	double det = A[0][0] * A[1][1] - A[0][1] * A[1][0];

	Ainv[0][0] = A[1][1]/det;
	Ainv[0][1] = -A[0][1]/det;
	Ainv[1][0] = -A[1][0]/det;
	Ainv[1][1] = A[0][0]/det;

	return Ainv;
}

Point get_circumcenter(double x1, double x2, double y1, double y2) {
	auto A = vector<vector<double>>(2, vector<double>(2));
	auto Ainv = vector<vector<double>>(2, vector<double>(2));
	auto Y = vector<double>(2);
	auto X = vector<double>(2);

	A[0][0] = x2, A[0][1] = y2;
	A[1][0] = x2-x1, A[1][1] = y2-y1;
	Y[0] = pow(x2,2)+ pow(y2,2);
	Y[1] = pow(x2,2) + pow(y2,2) - pow(x1,2) - pow(y1,2);

	Ainv = get_inv_2(A);
	
	X[0] = (Ainv[0][0] * Y[0] + Ainv[0][1] * Y[1])/2;
	X[1] = (Ainv[1][0] * Y[0] + Ainv[1][1] * Y[1])/2;

	return Point(X[0], X[1]);
}
