#ifndef COVER_H
#define COVER_H

#include <bitset>
#include <vector>
#include "instance.h"

using namespace std;

struct Cover {
	double w;
	bitset<100> mask;
	vector<int> covl;

	double theta, xc, yc;
	Cover();
	Cover(double theta, double xc, double yc);
	Cover(const Instance &ins, int ej, double theta, double xc, double yc);
	void operator=(const Cover &cov);
};

#endif
