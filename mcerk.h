#ifndef MCERK_H
#define MCERK_H

#include <vector>
#include <unordered_map>

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
		long long cnt_fupper = 0;
		long long cnt_fupper_s = 0;
		long long cnt_fupper_dp = 0;
		long long cnt_dp = 0;
		/**/


		/*backtracking functions*/
		void f(int ej, bitset<Instance::mask_size> mask, double wcurr);
		void _f(int ej, int k);

		/*upper-bound and cuts*/
		vector<double> wrem;
		double f_upper(int ej, bitset<Instance::mask_size> mask);

		unordered_map<bitset<Instance::mask_size>, double> mseen[10];
		unordered_map<bitset<Instance::mask_size>, double> dp[10];

};

#endif
