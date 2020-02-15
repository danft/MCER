#ifndef MCERK_H
#define MCERK_H

#include <vector>

using namespace std;

#include "mcer_base.h"
#include "context.h"
#include "solution.h"

class MCERK : public MCER_Base {
	public:
		Solution solve();
		MCERK(Context *context, CLS *cls);
	private:
		Context *context;
		CLS *cls;
		vector<bool> used;
		vector<bool> used_opt;
		void f(int ej, bitset<100> mask, int k, double wcurr);
		double wopt;
		vector<vector<double>> wrem;

		long long cntsols = 0;
};

#endif
