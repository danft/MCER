#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
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

int main() {

	vector<double> p_re = poly_re(2, 1, 1, 2.1, .3, -1.4);
	vector<double> p_im = poly_im(2, 1, 1, 2.1, .3, -1.4); 

	vector<complex<double>> pol;

	for (int j = 0; j<p_re.size(); j++)
	{
		if (j > 0)
			cout << "+";
		complex<double> cnum = complex<double>(p_re[j], p_im[j]);
		cout << "(";
		print_complex(p_re[j], p_im[j]);
		cout << ")z^" << j;
		pol.push_back(complex<double>(p_re[j], p_im[j]));
	}

	cout << endl;


	auto comp_matrix = vector<vector<complex<double>>>(6, vector<complex<double>>(6, complex<double>(0,0)));

	for (int i = 0; i<5; i++)
		comp_matrix[i][i+1] = complex<double>(1, 0);

	auto c_6 = complex<double>(p_re[6], p_im[6]);

	for (int i = 0; i<6; i++) 
	{
		auto ci = complex<double>(p_re[i], p_im[i]);
		comp_matrix[5][i] = -ci / c_6;
	}



	auto eig_values = vector<complex<double>>(6);

	eig(comp_matrix, eig_values);


	cout << "Roots: \n";
	for (int i = 0; i<eig_values.size(); i++) {
		cout << real(eig_values[i]) << " " << imag(eig_values[i]) << "i" << abs(eig_values[i]) << " [][] " << arg(eig_values[i]) << "\n";

		cout << "ERROR: " << poly_eval(pol, eig_values[i]) << endl;	
	}

	cout << "ERROR: " << poly_eval(pol, complex<double>(-1.0568, -4.64007)) << endl;

	return 0;
}

