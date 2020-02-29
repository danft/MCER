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

	generate_combs(0, context->instance->k);
	_f();

	context->times.push_back(clock() - t1);

	return Solution(
			context,
			get_opt(),
			cnt_leaves,
			cnt_nodes,
			used_opt);
}


double MCERK::f_upper(int ej, bitset<Instance::mask_size>mask, bool gr=false) {
	int m = context->instance->m;

	//if (mseen[ej].count(mask)){
	//	cnt_fupper_dp++;
	//	return mseen[ej][mask];
	//}

	cnt_fupper++;
	double ww = 0;

	vector<int> _opt;

	for (int j = ej; j<m; j++) if(used[j]) {
		const vector<Cover<Instance::mask_size>> &cls_list = cls->get_cls(j);
		double wbest = -1e9;
		int ibest = 0;

		for (int jj = 0; jj < cls_list.size(); jj++){
			auto& cov = cls_list[jj];
			double w = -context->instance->wel[j];

			for (int i : cov.covl)
				w+=context->instance->wpnt[i] * (!mask[i]);

			ibest = (w>wbest)?jj : ibest;
			wbest = max(wbest, w);
		}

		if (gr) {
			mask |= cls_list[ibest].mask;
			_opt.push_back(ibest);
			apply_cover(j, ibest);
		}

		ww += wbest;
	}

	if (gr){
		int ic = 0;
		cnt_leaves++;
		if (ww > wopt) {

			wopt = ww;
			set_opt();
			used_opt = used;
		}

		for (int j = ej; j<m; j++)
			if(used[j])
				remove_cover(j, _opt[ic++]);
	}

	return ww;
}

void MCERK::_f(){
	sort(combs.rbegin(), combs.rend());

	for (int i = 0; i<combs.size(); i++) {
		used = vector<bool>(context->instance->m,false);

		for (int j = 0; j<combs[i].second.size(); j++)
			used[combs[i].second[j]]=true;

		double lw = 0;
		for (int j = context->instance->m-1; j>=0; j--) {
			if (used[j]) {
				wrem[j] = cls->get_cls(j)[0].w + lw - context->instance->wel[j];
				lw = wrem[j];
			}
		}

		f(0, bitset<Instance::mask_size>(), 0);
	}
}

void MCERK::generate_combs(int ej, int k) {
	if (context->instance->m - ej < k) return;


	if (ej == context->instance->m){

		vector<int> tmp;
		for (int j = 0; j<context->instance->m; j++)
			if(used[j])
				tmp.push_back(j);

		combs.push_back(
				make_pair(
						f_upper(0, bitset<Instance::mask_size>(), false), tmp));


		return;
	}

	generate_combs(ej+1, k);
	if (k == 0)	return;


	used[ej] = true;
	generate_combs(ej+1, k-1);
	used[ej] = false;
}


void MCERK::f(int ej, bitset<Instance::mask_size> mask, double wcurr) {
	cnt_nodes++;

#ifdef DEBUG
	if (cnt_nodes % 1000000 == 0) {
		cout << ej << " " << cnt_fupper << " " << cnt_nodes << ", " << cnt_leaves << "----> " << wopt << endl;
		if (ej < context->instance->m){
			cout<< "CLS SIZE: " << context->cls->get_cls(ej).size() << endl;
		}

		cout << "cnt_fupper_s: " << cnt_fupper_s << endl;
		cout << "cnt_fupper_dp: " << cnt_fupper_dp << endl;
		cout << "cnt_dp: " << cnt_dp << endl;
		cout << "popcount: " << mask.count() << endl;
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
	if (wcurr + f_upper(ej, mask) - 1e-9 < wopt){
		cnt_fupper_s++;
		return;
	}

	double elcost = context->instance->wel[ej];
	const vector<Cover<Instance::mask_size>> &cls = context->cls->get_cls(ej);

	for (int j = 0;j < cls.size(); j++) 
		if (covers_any(mask, cls[j])) {
			double w = apply_cover(ej, j);

			f(ej+1, mask | cls[j].mask, wcurr + w - elcost);
			remove_cover(ej, j);
		}

	//dp[ej][mask] = 1;
}

