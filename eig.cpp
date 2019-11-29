#include <cmath>
#include <iostream>
#include "eig.h"

using namespace std;

//struct complex {double re; double im;};   

//typedef struct complex complex;

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
extern int zgeev_(
		char*,
		char*,
		int*,
		double*,
		int*,
		complex*, 
		complex**, 
		int*, 
		complex**,
		int*, 
		complex*, 
		int*, 
		complex*,
		int*);
}

int eig(vector<vector<complex>> &mat, vector<complex> &eig_values) {

	int size = mat.size();

	complex *WORK, *RWORK, *w, *vl[1], *vr[1];
	double AT[2 * size * size];

	vl[0] = new complex[size];
	vr[0] = new complex[size];
	w = new complex[size];
	WORK = new complex[size * 2];
	RWORK = new complex[size * 2];

	char jobvl = 'N';
	char jobvr = 'N';
	int ok, n, lda, ldvl, ldvr, lwork;


	n=size;
	jobvl='N';
	jobvr='N';
	lda=size;
	ldvl=1;
	ldvr=1;
	lwork=6;


	for (int i=0; i<size; i++)
		for(int j=0; j<size; j++)
		{
			AT[2*(j+size*i)]=mat[j][i].re;
			AT[2*(j+size*i)+1]=mat[j][i].im;
		}
	
	zgeev_(&jobvl, &jobvr,&n, AT, &lda, w, vl, &ldvl, vr, &ldvr, WORK, &lwork, 
  RWORK, &ok);

	if (ok == 0) 
	{
		for (int i = 0; i < size; i++) 
		{
			eig_values[i] = w[i];
			//printf("%f %f\n", eig_values[i].re, eig_values[i].im);
		}
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
