#include "instance.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

double todouble(string num) {
	double ret = 0, ax, bx;

	int epos = num.find('e');

	string a = num.substr(0, epos);
	string b = num.substr(epos+1, num.size() - epos - 1);

	if (epos == string::npos)
		b = "";

	stringstream astream = stringstream(a);
	stringstream bstream = stringstream(b);

	astream >> ax;
	
	if (b.size() > 0)
		bstream >> bx;
	else
		bx = 0;

	return ax * pow(10, bx);
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


