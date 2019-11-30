#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "eig.h"
#include "poly_function.h"

using namespace std;

int main() {

	vector<vector<complex>> A(2, vector<complex>(2));
	vector<complex> w(2);


	A[0][0].re = 1, A[0][0].im = 0;
	A[0][1].re = 1, A[0][1].im = 0;
	A[1][0].re = 1, A[1][0].im = 0;
	A[1][1].re = 0, A[1][1].im = 0;

	int ok = eig(A, w);

//	printf("%d\n", ok);

//printf("%f %f\n", w[0].re, w[0].im);
//	printf("%f %f\n", w[1].re, w[1].im);
	

	vector<double> p_re = poly_re(2, 1, 1, 2, 3, 4);
	vector<double> p_im = poly_im(2, 1, 1, 2, 3, 4);

	for (int j = 0; j<p_re.size(); j++)
		cout << p_re[j] << endl;

	cout << "-----" << endl;

	for (int j = 0; j<p_re.size(); j++)
		cout << p_im[j] << endl;




	return 0;
}

