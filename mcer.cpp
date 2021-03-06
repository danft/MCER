#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <bitset>
#include <set>
#include <ctime>
#include <iomanip>
#include <limits>

typedef std::numeric_limits<double> dbl;

#include "instance.h"
#include "subset_tree.h"
#include "cover.h"
#include "mcer_base.h"
#include "solver_wrapper.h"
#include "cls_mcer.h"

#include "mcer.h"

using namespace std;


MCER::MCER(Context *context, CLS *cls) : MCER_Base(context), context(context), cls(cls){
	n = context->instance->n;
	m = context->instance->m;
	wacc = vector<double>(m+1, 0);
	cnt_leaves = 0;
}

void MCER::_f(int el, bitset<Instance::mask_size> mask, double wcurr) {
	if (el == m) {
		cnt_leaves++;
		cnt_nodes++;
//	if (cntsols % 10000000 == 0)
//		cout << "[" << cntsols << "]: " << best_sol_v <<  "time: " << 1.0*(clock()-t3) / CLOCKS_PER_SEC << " s"<< endl;

		if (wcurr > wopt) {
			set_opt();
			wopt = wcurr;
		}

		return;
	}

	double ret = 0;
	// if the best cover is used for the rest of the ellipses.
	double w_rem = wacc[m] - wacc[el];

	if (wcurr + w_rem <= wopt){
		cnt_leaves++;
		cnt_nodes++;
		return;
	}

	//const vector<Cover> &cls = context->cls_list[el];

	for (int j = 0; j<context->cls->get_cls(el).size(); j++) {
		if (!covers_any(mask, context->cls->get_cls(el)[j])) continue;

		double wsum = apply_cover(el, j);
		_f(el + 1, mask | context->cls->get_cls(el)[j].mask, wcurr + wsum);
		remove_cover(el, j);
	}

	cnt_nodes++;
}

Solution MCER::solve() {
	// Specific cut.
	for (int i = 0; i<m; i++) {
		wacc[i+1] = wacc[i] + context->cls->get_cls(i)[0].w;
	}

	clock_t t1 = clock();
	_f(0, bitset<Instance::mask_size>(0), 0);
	context->times.push_back(clock()-t1);

	return Solution(context, get_opt(), cnt_leaves, cnt_nodes);
}



