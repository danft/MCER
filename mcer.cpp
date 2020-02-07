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
#include "isolver.h"
#include "solver_wrapper.h"

using namespace std;

vector<vector<Cover>> MCER1(Instance instance) {

	auto covs = vector<vector<Cover>>(instance.m);

	for (int l = 0; l<instance.m; ++l) {
		double a = instance.a[l];
		double b = instance.b[l];
		STree tree = STree(instance.n);

		vector<Cover> c_tmp;

		for (int i = 0; i<instance.n; i++) {
			Cover cov = Cover(instance, l, 0, instance.X[i], instance.Y[i]);

			if (!tree.has(cov.covl)) {
				c_tmp.push_back(cov);
				tree.add_nodes(cov.covl);
			}

			for (int j = i+1; j<instance.n; ++j) {
				
				vector<pair<double, Point>> sols = e2p(a, b, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j]);

				for (int h = 0; h<sols.size(); h++) {
					cov = Cover(instance, l, sols[h].first, sols[h].second.x, sols[h].second.y);

					if (!tree.has(cov.covl))
					{
						c_tmp.push_back(cov);
						tree.add_nodes(cov.covl);
					}
				}

				for (int k = j+1; k < instance.n; ++k)
				{
					sols = e3p(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k]);

					for (int h = 0; h < sols.size(); h++) {
						cov = Cover(instance, l, sols[h].first, sols[h].second.x, sols[h].second.y);

						if (!tree.has(cov.covl))
						{
							c_tmp.push_back(cov);
							tree.add_nodes(cov.covl);
						}
					}
				}
			}
		}

		sort(c_tmp.begin(), c_tmp.end(), [](const Cover &ca, const Cover &cb)->bool {return ca.covl.size() > cb.covl.size();});

		STree tree2 = STree(instance.n);


		for (auto c : c_tmp) 
		{
			if (!tree2.has(c.covl)) 
			{
				//cout << l << ": " << c.covl.size() << endl;
				tree2.add_nodes(c.covl);
				covs[l].push_back(c);
			}
		}

		sort(covs[l].begin(), covs[l].end(), [](const Cover &ca, const Cover &cb)->bool {return ca.w > cb.w;});
	}

	return covs;
}

struct MCER : ISolver {
	
	/*Each list is sorted descending by its weight.*/
	vector<vector<Cover>> covers;

	/*Accumulated sum of best covers from each ellipse (1-based)*/
	vector<double> wacc; 

	/*The instance*/
	Instance instance;

	/*current solution*/
	vector<int> curr;

	/*best solution found so far.*/
	vector<int> best_sol;

	/*says how many ellipses covers i-th point.*/
	vector<int> cov_cnt;

	/*value of the best solution found so far.*/
	double best_sol_v;

	/*Counts the number of solutions that has been looked at.*/
	long long cntsols = 0;

	/*Time measurements.*/
	clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;

	/*Tells if a state has been visited already*/
	vector<set<bitset<100>>> seen;
	
	MCER(Instance ins) : instance(ins){
		curr = vector<int>(instance.m);
		best_sol = vector<int>(instance.m);
		wacc = vector<double>(instance.m+1, 0);
		seen = vector<set<bitset<100>>>(instance.m);
		cov_cnt = vector<int>(instance.n, 0);
	}

	Solution solve() {

		vector<clock_t> times;

		t1 = clock();

		covers = MCER1(instance);

		for (int i = 0; i<instance.m; i++)
			wacc[i+1] = wacc[i] + covers[i][0].w;

		times.push_back(clock()-t1);

		t3 = clock();

		_f(0, bitset<100>(0), 0);

		times.push_back(clock()-t3);

		return Solution(instance, covers, best_sol, cov_cnt, times, cntsols, best_sol_v);
	}

	double apply_cover(int el, int jcov, int mul=1) {
		double wret = 0;

		int cmp = (mul>0) ? 0 : 1;

		for (int i = 0; i<covers[el][jcov].covl.size(); i++) {
			int jpnt = covers[el][jcov].covl[i];

			wret += instance.wpnt[jpnt] * (cov_cnt[jpnt] == cmp);

			cov_cnt[jpnt] += mul;
		}

		return wret;
	}

	double remove_cover(int el, int jcov) {
		return apply_cover(el, jcov, -1);
	}

	double _f(int el, bitset<100> mask, double wcurr) {
		if (el == instance.m) {
			
			cntsols++;

			if (cntsols % 10000000 == 0)
				cout << "[" << cntsols << "]: " << best_sol_v <<  "time: " << 1.0*(clock()-t3) / CLOCKS_PER_SEC << " s"<< endl;

			double w = 0;

			for (int i = 0;i < instance.n; i++)
				w += mask[i] * instance.wpnt[i];

			if (w > best_sol_v) {
				best_sol = curr;
				best_sol_v = w;
			}

			return 0;
		}

		double ret = 0;

		// if the best cover is used for the rest of the ellipses.
		double w_rem = wacc[instance.m] - wacc[el];

		if (wcurr + w_rem <= best_sol_v) return wcurr + w_rem;


		for (int j = 0; j<covers[el].size(); j++) {
			if ((covers[el][j].mask | mask) == mask) continue;

			curr[el] = j;

			double wsum = apply_cover(el, j);

			ret = max(ret, _f(el + 1, mask | covers[el][j].mask, wcurr + wsum) + wsum);

			remove_cover(el, j);
		}

		return ret;
	}
};

int main() {
	
	auto instance = read_instance_from_file(cin);

	MCER mcer = MCER(instance);

	solve(mcer, instance);

	return 0;
}

