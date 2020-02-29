#include <vector>
#include <cmath>
#include <complex>

#include "eig.h"

using namespace std;

vector<complex<double>> roots(vector<complex<double>> &pol) {

	int n = 6;
	while (n >= 0 && abs(pol[n]) < 1e-9)
		n--;

	if (n < 0)
		return vector<complex<double>>();

	auto comp_matrix = vector<vector<complex<double>>>(n, vector<complex<double>>(n, complex<double>(0,0)));

	for (int i = 0; i<n-1; i++)
		comp_matrix[i][i+1] = complex<double>(1, 0);

	for (int i = 0; i<n; i++) 
		comp_matrix[n-1][i] = -pol[i] / pol[n];

	auto eig_values = vector<complex<double>>(n);
	eig(comp_matrix, eig_values);

	return eig_values;
}
