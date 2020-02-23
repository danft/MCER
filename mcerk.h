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


		/*solution details*/
		vector<bool> used;
		vector<bool> used_opt;
		double wopt;
		long long cnt_leaves = 0;
		long long cnt_nodes = 0;
		/**/


		/*backtracking functions*/
		void f(int ej, bitset<Instance::mask_size> mask, double wcurr);
		void _f(int ej, int k);

		/*upper-bound and cuts*/
		vector<vector<double>> wrem;
		double f_upper(int ej, bitset<Instance::mask_size> mask);
};

#endif
