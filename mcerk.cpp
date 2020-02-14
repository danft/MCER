#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#include "mcerk.h"
#include "mcer_base.h"

MCERK::MCERK(Context *context) : MCER_Base(context), context(context){
	used = vector<bool>(context->instance->m, false);
	used_opt = vector<bool>(context->instance->m, false);
	wrem = vector<vector<double>>(
			context->instance->m,
			vector<double>(context->instance->m+1, 0));
	wopt = 0;
	cntsols = 0;
}

Solution MCERK::solve() {
	create_CLS();



	for (int i = 0; i<context->instance->m; i++) {
		vector<double> w2 = vector<double>(context->instance->m-i, 0);

		const vector<Cover> &cls = context->cls_list[i];

		for (int j = i; j<context->instance->m; j++)
			w2.push_back(cls[0].w);
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
	
	const vector<Cover> &cls = context->cls_list[ej];

	for (int j = 0;j < cls.size(); j++) 
		if (covers_any(mask, cls[j])) {
			used[ej] = true;
			double w = apply_cover(ej, j);

			f(ej+1, mask | cls[j].mask, k-1, wcurr + w);
			remove_cover(ej, j);
		}

	used[ej] = false;
}

