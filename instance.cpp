#include "instance.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

Instance read_instance_from_file(char const*  filename) {
	ifstream infile;
	infile.open(filename);

	if (!infile) 
	{
		cout << "Unable to open file" << endl;
		exit(1);
	}

	Instance ret = Instance();
	
	infile >> ret.m >> ret.k;

	ret.a = vector<double>(ret.m);
	ret.b = vector<double>(ret.m);
	ret.wel = vector<double>(ret.m);

	for (int i = 0; i<ret.m; i++)
		infile >> ret.a[i] >> ret.b[i];

	for (int i = 0; i<ret.m; i++)
		infile >> ret.wel[i] >> ret.wel[i];

	infile >> ret.n;

	ret.X = vector<double>(ret.n);
	ret.Y = vector<double>(ret.n);
	ret.wpnt = vector<double>(ret.n);

	for (int i = 0; i<ret.n; i++)
		infile >> ret.X[i] >> ret.Y[i];

	for (int i = 0; i<ret.n; i++)
		infile >> ret.wpnt[i];

	infile.close();

	return ret;
}


