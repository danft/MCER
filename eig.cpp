#include <cmath>
#include <iostream>
#include <complex>
#include "eig.h"

using namespace std;

typedef struct ccomplex {double re; double im;} ccomplex; 

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
extern int zgeev_(
		char*,
		char*,
		int*,
		double*,
		int*,
		ccomplex*, 
		ccomplex**, 
		int*, 
		ccomplex**,
		int*, 
		ccomplex*, 
		int*, 
		ccomplex*,
		int*);
}

int eig(vector<vector<complex<double>>> &mat, vector<complex<double>> &eig_values) {

	int size = mat.size();

	ccomplex *WORK, *RWORK, *w, *vl[1], *vr[1];
	double AT[2 * size * size];

	vl[0] = new ccomplex[size];
	vr[0] = new ccomplex[size];
	w = new ccomplex[size];
	WORK = new ccomplex[size * 2];
	RWORK = new ccomplex[size * 2];

	char jobvl = 'N';
	char jobvr = 'N';
	int ok, n, lda, ldvl, ldvr, lwork;


	n=size;
	jobvl='N';
	jobvr='N';
	lda=size;
	ldvl=1;
	ldvr=1;
	lwork=size * 2;


	for (int i=0; i<size; i++)
		for(int j=0; j<size; j++)
		{
			AT[2*(j+size*i)]=real(mat[j][i]);
			AT[2*(j+size*i)+1]=imag(mat[j][i]);
		}
	
	zgeev_(&jobvl, &jobvr,&n, AT, &lda, w, vl, &ldvl, vr, &ldvr, WORK, &lwork, RWORK, &ok);

	if (ok == 0) 
	{
		for (int i = 0; i < size; i++) 
			eig_values[i] = complex<double>(w[i].re, w[i].im);
	}

#ifdef DEBUG
	for (int i = 0;i < 3; i++) {
		printf("%f %f\n", w[i].re, w[i].im);
	}
#endif


	delete[] vl[0];
	delete[] vr[0];
	delete[] WORK;
	delete[] RWORK;

	return !ok;
}
