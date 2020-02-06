#include "isolver.h"
#include "solver_wrapper.h"
#include "instance.h"

#include <iostream>

using namespace std;

void solve(ISolver &solver, Instance &ins) {
	cout << ins.to_string() << endl;

	solver.solve();

	//cout << solver.to_string() << endl;
}
