#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

using namespace std;

struct Instance {
	vector<double> a, b, wel, wpnt;
	vector<double> X, Y;
	int n, m, k;

	Instance() {
	}
};

Instance read_instance_from_file(char const *filename);


#endif