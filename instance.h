#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Instance {
	vector<double> a, b, wel, wpnt;
	vector<double> X, Y;
	int n, m, k;
	const static size_t mask_size = 500;

	string info() const;
	Instance() {
		n=m=k=0;
	}
};

//Instance read_instance_from_file(char const *filename);
Instance read_instance_from_file(istream &infile);


#endif
