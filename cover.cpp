#include "cover.h"
#include "utils.h"
#include "instance.h"

Cover::Cover() {
	w = 0;
	mask = bitset<100>(0);
	covl = vector<int>();
}

Cover::Cover(double theta, double xc, double yc) : xc(xc), yc(yc), theta(theta) {
	w = 0;
	mask = bitset<100>(0);
	covl = vector<int>();
}

Cover::Cover(const Instance &ins, int ej, double theta, double xc, double yc): Cover(xc, yc, theta){

	for (int i = 0; i<ins.n; i++) 
		if (eval_ellipse(ins.a[ej], ins.b[ej], theta, xc, yc, ins.X[i], ins.Y[i]) -1e-15 < 1)
		{
			mask.set(i);
			w += ins.wpnt[i];
			covl.push_back(i);
		}
}

void Cover::operator=(const Cover &cov) {
	mask = cov.mask;
	w = cov.w;
	theta = cov.theta;
	xc = cov.xc;
	yc = cov.yc;
	covl = cov.covl;
}
