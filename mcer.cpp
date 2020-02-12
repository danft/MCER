#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <bitset>
#include <set>
#include <ctime>
#include <iomanip>
#include <limits>

typedef std::numeric_limits<double> dbl;

#include "e3p.h"
#include "e2p.h"
#include "instance.h"
#include "subset_tree.h"
#include "cover.h"
#include "mcer_base.h"
#include "solver_wrapper.h"
#include "cls_mcer.h"

using namespace std;


class MCER : public MCER_Base {
	public:

		/*The instance*/

		MCER(Context *context) : MCER_Base(context), context(context){
			n = context->instance->n;
			m = context->instance->m;
			curr = vector<int>(m);
			best_sol = vector<int>(m);
			wacc = vector<double>(m+1, 0);
			seen = vector<set<bitset<100>>>(m);
			times = vector<clock_t>();
			cntsols = 0;
		}

		double _f(int el, bitset<100> mask, double wcurr) {
			if (el == m) {
				cntsols++;


//				if (cntsols % 10000000 == 0)
//			cout << "[" << cntsols << "]: " << best_sol_v <<  "time: " << 1.0*(clock()-t3) / CLOCKS_PER_SEC << " s"<< endl;


				double w = 0;
				for (int i = 0;i < n; i++)
					w += mask[i] * context->instance->wpnt[i];

				if (w > best_sol_v)
				{
					best_sol = curr;
					best_sol_v = w;
					covered_list = get_covered_list();
				}

				return 0;
			}

			double ret = 0;
			// if the best cover is used for the rest of the ellipses.
			double w_rem = wacc[m] - wacc[el];

			if (wcurr + w_rem <= best_sol_v) return wcurr + w_rem;

			const vector<Cover> &cls = (*context->covers)[el];

			for (int j = 0; j<cls.size(); j++) {
				if ((cls[j].mask | mask) == mask) continue;

				curr[el] = j;
				double wsum = apply_cover(el, j);
				ret = max(ret, _f(el + 1, mask | cls[j].mask, wcurr + wsum) + wsum);
				remove_cover(el, j);
			}

			return ret;
		}

		Solution solve() {

			create_CLS();

			for (int i = 0; i<m; i++) {
				wacc[i+1] = wacc[i] + (*context->covers)[i][0].w;
			}

			t1 = clock();

			_f(0, bitset<100>(0), 0);	

			times.push_back(clock() - t1);

			vector<Cover> opt_cov;

			for (int i = 0; i<m; i++) {
				opt_cov.push_back(
						(*context->covers)[i][best_sol[i]]);	
			}

			return Solution(
					context, 
					best_sol, 
					times, 
					cntsols);
		}

	private:
		Context *context;
		vector<int> curr;
		vector<int> covered_list;
		vector<int> best_sol;
		vector<double> wacc; 
		vector<set<bitset<100>>> seen;
		vector<clock_t> times;
		double best_sol_v = 0;
		long long cntsols; 
		int n, m;

};

int main() {

	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance);

	MCER mcer = MCER(&context);

	solve(mcer, instance);

	return 0;
}

