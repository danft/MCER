#include <cmath>
#include <iostream>
#include <complex>
#include "eig.h"

using namespace std;

typedef struct ccomplex {double re; double im;} ccomplex; 

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
extern int zgeev_(
		char*,			/*JOBVL*/
		char*,			/*JOBVR*/
		int*,			/*N*/
		double*,		/*A*/
		int*,			/*LDA*/
		ccomplex*,		/*W*/ 
		ccomplex**,		/*VL*/
		int*, 			/*LDVL*/
		ccomplex**,		/*VR*/
		int*, 			/*LDVR*/
		ccomplex*, 		/*WORK*/
		int*, 			/*LWORK*/
		ccomplex*,		/*RWORK*/
		int*);			/*INFO*/
}

int eig(vector<vector<complex<double>>> &mat, vector<complex<double>> &eig_values) {

	ccomplex WORK[20], RWORK[20], w[20];
	ccomplex *vl[1], *vr[1];

	char jobvl = 'N';
	char jobvr = 'N';
	int ok, n, lda, ldvl, ldvr, lwork;
	int size = mat.size();
	double AT[2 * size * size];


	vl[0] = new ccomplex[size];
	vr[0] = new ccomplex[size];
	//w = new ccomplex[size];
	//WORK = new ccomplex[size * 2];
	//RWORK = new ccomplex[size * 2];
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
		//cout << endl;
		///cout << "ROOTS:\n";
		for (int i = 0; i < size; i++) {
			eig_values[i] = complex<double>(w[i].re, w[i].im);
			//cout << w[i].re << ' ' << w[i].im << "j\n";
		}
	}

	delete[] vl[0];
	delete[] vr[0];
	//delete[] WORK;
	//delete[] RWORK;

	return !ok;
}
