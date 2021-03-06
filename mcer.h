#ifndef MCER_H
#define MCER_H

#include <vector>
#include <set>
#include <bitset>

using namespace std;

#include "context.h"
#include "solution.h"
#include "mcer_base.h"

class MCER : public MCER_Base {
	public:
		MCER(Context *context, CLS *cls);
		Solution solve();

	private:
		void _f(int el, bitset<Instance::mask_size> mask, double wcurr);

		Context *context;
		CLS *cls;
		vector<double> wacc;
		double wopt = 0;
		long long cnt_leaves = 0;
		long long cnt_nodes = 0;
		int n, m;
};

#endif
