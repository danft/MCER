#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "eig.h"

using namespace std;

int main() {

	vector<vector<complex>> A(2, vector<complex>(2));
	vector<complex> w(2);


	A[0][0].re = 1, A[0][0].im = 0;
	A[0][1].re = 1, A[0][1].im = 0;
	A[1][0].re = 1, A[1][0].im = 0;
	A[1][1].re = 0, A[1][1].im = 0;

	int ok = eig(A, w);

	printf("%d\n", ok);

	printf("%f %f\n", w[0].re, w[0].im);
	printf("%f %f\n", w[1].re, w[1].im);
	


	return 0;
}

