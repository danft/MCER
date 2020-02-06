#include "instance.h"
#include "utils.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
#include <sstream>

using namespace std;

string Instance::to_string() {

 	ostringstream ss;	

	ss << "Instance: n=" << n << ", m=" << m << ", k=" << k << endl;

	string elp[] = {", ", "]\n"};

	ss << "a = [";

	for (int i = 0; i<m; i++)
		ss << a[i] << elp[i+1==m];

	ss << "b = [";
	for (int i = 0; i<m; i++) 
		ss << b[i] << elp[i+1==m];

	ss << "wel = [";
	for (int i = 0; i<m; i++) 
		ss << wel[i] << elp[i+1==m];

	ss << "X = [";

	for (int i = 0; i<X.size(); i++)
		ss << X[i] << elp[i+1==n];

	ss << "Y = [";
	for (int i = 0; i<Y.size(); i++) 
		ss << Y[i] << elp[i+1==n];

	ss << "wpnt = [";
	for (int i = 0; i<Y.size(); i++) 
		ss << wpnt[i] << elp[i+1==n];

	ss << endl;

	return ss.str();
}

//Instance read_instance_from_file(char const*  filename) {
Instance read_instance_from_file(istream &infile) {
	//ifstream infile;
	//infile.open(filename);

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

	for (int i = 0; i<ret.m; i++) {
		string a, b;
		infile >> a >> b;
		ret.a[i] = todouble(a);
		ret.b[i] = todouble(b);
	}

	for (int i = 0; i<ret.m; i++) {
		string wel;
		infile >> wel;
		ret.wel[i] = todouble(wel);
	}

	infile >> ret.n;

	ret.X = vector<double>(ret.n);
	ret.Y = vector<double>(ret.n);
	ret.wpnt = vector<double>(ret.n);

	for (int i = 0; i<ret.n; i++) {
		string X, Y;
		infile >> X >> Y;
		ret.X[i] = todouble(X);
		ret.Y[i] = todouble(Y);
	}

	for (int i = 0; i<ret.n; i++) {
		string wpnt;
		infile >> wpnt;
		ret.wpnt[i] = todouble(wpnt);
	}

	//infile.close();

	return ret;
}


