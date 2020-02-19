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
	cntsols = 0;
}

Solution MCERK::solve() {

	create_CLS(cls);

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

	f(0, bitset<100>(), context->instance->k, 0);

	context->times.push_back(clock() - t1);

	return Solution(
			context,
			get_opt(),
			cntsols,
			used_opt);
}

void MCERK::f(int ej, bitset<100> mask, int k, double wcurr) {
	if (ej == context->instance->m) {
		if (k>0) return;

		cntsols++;

		if (wcurr > wopt)
		{
			set_opt();
			wopt = wcurr;
			used_opt = used;
		}

		return;
	}

	if (wcurr + wrem[ej][k] <= wopt) return;

	used[ej] = false;
	f(ej+1, mask, k, wcurr);
	if (k==0) return;
	
	double elcost = context->instance->wel[ej];

	const vector<Cover> &cls = context->cls_list[ej];

	for (int j = 0;j < cls.size(); j++) 
		if (covers_any(mask, cls[j])) {
			used[ej] = true;
			double w = apply_cover(ej, j);

			f(ej+1, mask | cls[j].mask, k-1, wcurr + w - elcost);
			remove_cover(ej, j);
		}

	used[ej] = false;
}

