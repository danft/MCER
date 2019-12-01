#include <iostream>
#include <vector>
#include <fstream>
#include "e3p.h"
#include "instance.h"

using namespace std;


void MCER1(Instance instance) {
	
	int a = instance.a[0];
	int b = instance.b[0];

	for (int i = 0; i<instance.n; i++)
		for (int j = i+1; j<instance.n; ++j)
			for (int k = j+1; k < instance.n; ++k)
			{
				auto sols = e3p(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k]);

				
				for (int h = 0; h < sols.size(); h++)
					cout << sols[h] << endl;

	//			cout << i << " " << j << " " << k << endl;
			}
}

int main() {

	auto instance = read_instance_from_file("instances/danft1.txt");

	//MCER1(instance);

	cout << instance.k << endl;

	for (int i = 0;i < instance.n; ++i)
		cout << instance.X[i] << " " << instance.Y[i] << endl;
	cout << endl;


	return 0;
}

