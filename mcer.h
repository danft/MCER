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
		MCER(Context *context);
		Solution solve();

	private:
		void _f(int el, bitset<100> mask, double wcurr);

		Context *context;

		vector<double> wacc;
		double wopt = 0;
		long long cntsols;
		int n, m;
};

#endif
