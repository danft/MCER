#ifndef COVER_H
#define COVER_H

#include <bitset>
#include <vector>
#include "instance.h"

using namespace std;

template<std::size_t N>
class Cover{
public:
	double w;
	bitset<N> mask;
	vector<int> covl;

	double theta, xc, yc;
	Cover();
	Cover(double theta, double xc, double yc);
	Cover(const Instance &ins, int ej, double theta, double xc, double yc);
	void operator=(const Cover &cov);
};

#endif
