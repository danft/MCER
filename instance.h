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

	string to_string();
	Instance() {
	}
};

//Instance read_instance_from_file(char const *filename);
Instance read_instance_from_file(istream &infile);


#endif
