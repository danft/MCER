#include "isolver.h"
#include "solver_wrapper.h"
#include "solution.h"
#include "instance.h"

#include <iostream>

using namespace std;

void solve(ISolver &solver, Instance &ins) {
	cout << ins.info() << endl;

	Solution sol = solver.solve();

	cout << sol.info() << endl;
}
