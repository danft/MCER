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
	wrem = vector<double>(context->instance->m+1, 0);
	wopt = -1e9;
	cnt_leaves = 0;
}

Solution MCERK::solve() {

	create_CLS(cls);

#ifdef DEBUG
	cout << endl;
	cout << "CLS Construction Finished" << endl;

	for (int i = 0; i<context->instance->m; i++)
		cout << "CLS Size: " << i+1 << ": " << context->cls->get_cls(i).size()<<endl;
	cout << endl;
#endif

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
		const vector<Cover<Instance::mask_size>> &cls_list = cls->get_cls(j);
		double wbest = -1e9;
		int ibest = 0;

		for (int jj = 0; jj < cls_list.size(); jj++){
			auto& cov = cls_list[jj];
			double w = -context->instance->wel[j];

			for (int i : cov.covl)
				w+=context->instance->wpnt[i] * (!mask[i]);

			if (w > wbest){
				wbest = w;
				ibest = jj;
			}
		}

		ww += wbest;
		//mask |= cls_list[ibest].mask;
	}

	return ww;
}

void MCERK::_f(int ej, int k) {
	if (context->instance->m - ej < k) return;

	if (ej == context->instance->m){

		double lw = 0;
		for (int j = context->instance->m-1; j>=0; j--)
			if (used[j]) {
				wrem[j] = cls->get_cls(j)[0].w + lw - context->instance->wel[j];
				lw = wrem[j];
			}

		f(0, bitset<Instance::mask_size>(), 0);
		return;
	}

	_f(ej+1, k);
	if (k == 0)	return;


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
			cout<< "CLS SIZE: " << context->cls->get_cls(ej).size() << endl;
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

	if (wcurr + wrem[ej] -1e-9 < wopt) return;
	if (wcurr + f_upper(ej, mask) - 1e-9 < wopt) return;

	//if (is_seen(ej, mask)) return;
	//add_seen(ej, mask);

	//if (wcurr + wrem[ej][k] <= wopt) return;

	double elcost = context->instance->wel[ej];

	const vector<Cover<Instance::mask_size>> &cls = context->cls->get_cls(ej);

	for (int j = 0;j < cls.size(); j++) 
		if (covers_any(mask, cls[j])) {
			double w = apply_cover(ej, j);

			f(ej+1, mask | cls[j].mask, wcurr + w - elcost);
			remove_cover(ej, j);
		}
}

