#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "e3p.h"
#include "eig.h"
#include "poly_function.h"

using namespace std;

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

/*test*/
int test() {

	auto angles = e3p(2, 1, 1, 1.1, -1.3, 3);

	for (auto a : angles){
		cout << a << endl;
	}

	return 0;
}

vector<complex<double>> e3p_get_polynomial(double a, double b, double x1, double x2, double y1, double y2) {

	vector<double> p_re = poly_re(a, b, x1, x2, y1, y2);
	vector<double> p_im = poly_re(a, b, x1, x2, y1, y2);

	vector<complex<double>> pol;

	for (int j = 0; j<p_re.size(); j++)
		pol.push_back(complex<double>(p_re[j], p_im[j]));

	return pol;
}

vector<complex<double>> e3p_get_roots(double a, double b, double x1, double x2, double y1, double y2) {

	auto pol = e3p_get_polynomial(a, b, x1, x2, y1, y2);	

	auto comp_matrix = vector<vector<complex<double>>>(6, vector<complex<double>>(6, complex<double>(0,0)));

	for (int i = 0; i<5; i++)
		comp_matrix[i][i+1] = complex<double>(1, 0);

	int n = 6;

	reverse(pol.begin(), pol.end());

	while (n >= 0 && abs(pol[n]) < 1e-15) 
		n--;

	for (int i = 0; i<n; i++) 
		comp_matrix[5][i] = -pol[i] / pol[n];

	auto eig_values = vector<complex<double>>(n);
	eig(comp_matrix, eig_values);

	return eig_values;
}

bool is_colinear(double x1, double x2, double y1, double y2) {
	return abs(x1 * y2 - x2 * y1) < 1e-15;
}

vector<double> e3p(double a, double b, double x0, double x1, double x2, double y0, double y1, double y2) {
	return e3p(a, b, x1-x0, x2-x0, y1-y0, y2-y0);
}	

vector<double> e3p(double a, double b, double x1, double x2, double y1, double y2) {
	if (is_colinear(x1, x2, y1, y2))
	{
		return vector<double>();
	}

	auto roots = e3p_get_roots(a, b, x1, x2, y1, y2);

	vector<double> ret;

	for (auto r : roots) 
	{
		//cout << r << "  ----- " << abs(1-abs(r)) << endl;
		if (abs(abs(r) - 1) < 1e-1)
			ret.push_back(arg(r));
	}

	return ret;
}

