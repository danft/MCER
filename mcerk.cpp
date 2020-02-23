#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#include "mcerk.h"
#include "mcer_base.h"
#include "cls_mcer.h"

MCERK::MCERK(Context *ctx, CLS *cls_) : MCER_Base(ctx), context(ctx), cls(cls_){
	used = vector<bool>(context->instance->m, false);
	used_opt = vector<bool>(context->instance->m, false);
	wrem = vector<vector<double>>(
			context->instance->m,
			vector<double>(context->instance->m+1, 0));
	wopt = -1e9;
	cnt_leaves = 0;
}

Solution MCERK::solve() {

	create_CLS(cls);

#ifdef DEBUG
	cout << endl;
	cout << "CLS Construction Finished" << endl;

	for (int i = 0; i<context->instance->m; i++)
		cout << "CLS Size: " << i+1 << ": " << context->cls_list[i].size()<<endl;
	cout << endl;
#endif

	for (int i = 0; i<context->instance->m; i++) {
		vector<double> w2 = vector<double>(context->instance->m-i, 0);

		for (int j = i; j<context->instance->m; j++)
			w2.push_back(context->cls_list[i][0].w - context->instance->wel[j]);
		sort(w2.rbegin(), w2.rend());

		wrem[i][0] = 0;

		for (int j = 1; j<=context->instance->m-i; j++)
			wrem[i][j] = wrem[i][j-1] + w2[j-1];
	}

	clock_t t1 = clock();

	_f(0, context->instance->k);

	context->times.push_back(clock() - t1);

	return Solution(
			context,
			get_opt(),
			cnt_leaves,
			cnt_nodes,
			used_opt);
}


double MCERK::f_upper(int ej, bitset<Instance::mask_size>mask) {
	int m = context->instance->m;

	double ww = 0;

	for (int j = ej; j<m; j++) if(used[j]) {
		vector<Cover<Instance::mask_size>> &cls_list = context->cls_list[j];
		double wbest = -1e9;
		int ibest = 0;

		for (int jj = 0; jj < cls_list.size(); jj++){
			auto& cov = cls_list[jj];
			double w = -context->instance->wel[j];

			for (int i : cov.covl)
				if (!mask[i])
					w+=context->instance->wpnt[i];

			if (w > wbest){
				wbest = w;
				ibest = jj;
			}
		}

		ww += wbest;
		mask |= cls_list[ibest].mask;
	}

	return ww;
}

void MCERK::_f(int ej, int k) {
	if (ej == context->instance->m){
		f(0, bitset<Instance::mask_size>(), 0);
		return;
	}

	if (context->instance->m - ej < k) return;
	if (k == 0){
		_f(ej+1, k);
		return;
	}

	used[ej] = true;
	_f(ej+1, k-1);
	used[ej] = false;
}


void MCERK::f(int ej, bitset<Instance::mask_size> mask, double wcurr) {
	cnt_nodes++;

#ifdef DEBUG
	if (cnt_nodes % 100000000 == 0) {
		cout << ej << " " << context->instance->m << " " << cnt_nodes << "----> " << wopt << endl;
		if (ej < context->instance->m){
			cout<< "CLS SIZE: " << context->cls_list[ej].size() << endl;
		}
	}
#endif

	if (ej == context->instance->m) {

		cnt_leaves++;

		if (wcurr > wopt){
			set_opt();
			wopt = wcurr;
			used_opt = used;
		}

		return;
	}

	if (!used[ej]) {
		f(ej+1, mask, wcurr);
		return;
	}

	if (ej > 0 && wcurr + f_upper(ej, mask) <= wopt) return;
	//if (wcurr + wrem[ej][k] <= wopt) return;

	double elcost = context->instance->wel[ej];

	const vector<Cover<Instance::mask_size>> &cls = context->cls_list[ej];

	for (int j = 0;j < cls.size(); j++) 
		if (covers_any(mask, cls[j])) {
			double w = apply_cover(ej, j);

			f(ej+1, mask | cls[j].mask, wcurr + w - elcost);
			remove_cover(ej, j);
		}
}

