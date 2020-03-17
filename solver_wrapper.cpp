#include "mcer_base.h"
#include "solver_wrapper.h"
#include "solution.h"
#include "instance.h"
#include "context.h"

#include <iostream>

using namespace std;

void solve(MCER_Base &solver, const Context *context) {
	if (context->print_info)
		cout << context->instance->info() << endl;

	Solution sol = solver.solve();

	if (context->print_info)
		cout << sol.info(context->precision) << endl;

	if (context->print_table)
		cout << sol.table() << endl;

	if (context->print_list)
		cout << sol.list() << endl;
}
