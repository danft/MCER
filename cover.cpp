#include "cover.h"
#include "utils.h"
#include "instance.h"

template<std::size_t N>
Cover<N>::Cover(): Cover(0, 0, 0){
}

template<std::size_t N>
Cover<N>::Cover(double xc, double yc, double theta) : xc(xc), yc(yc), theta(theta) {
	w = 0;
	mask = bitset<N>(0);
	covl = vector<int>();
}

template<std::size_t N>
Cover<N>::Cover(const Instance &ins, int ej, double xc, double yc, double theta)
: xc(xc), yc(yc), theta(theta){

	w = 0;
	mask = bitset<N>(0);
	covl = vector<int>();
	for (int i = 0; i<ins.n; i++) 
		if (eval_ellipse(ins.a[ej], ins.b[ej], theta, xc, yc, ins.X[i], ins.Y[i]) -1e-9 < 1)
		{
			mask.set(i);
			w += ins.wpnt[i];
			covl.push_back(i);
		}
}

template<std::size_t N>
void Cover<N>::operator=(const Cover<N> &cov) {
	mask = cov.mask;
	w = cov.w;
	theta = cov.theta;
	xc = cov.xc;
	yc = cov.yc;
	covl = cov.covl;
}

template class Cover<Instance::mask_size>;
