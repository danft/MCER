#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <set>
#include "cover.h"
#include "context.h"
#include "instance.h"

using namespace std;

class Solution {
	public:
	
	string info(int precision) const;
	string table() const;
	string list() const;

	Solution(Context *context, vector<int> opt, long long nleaves, long long nnodes);
	Solution(Context *context, vector<int> opt, long long nleaves, long long nnodes, vector<bool> used);

	Solution();

	private:
	void add_to_cover(const Cover<Instance::mask_size> &cov);
	double get_sol_val() const;
	string used_str(string spr) const;

	Instance instance;
	vector<Cover<Instance::mask_size>> opt_cov;
	vector<clock_t> time_ellapsed;
	set<int> cov_set;
	vector<size_t> cls_size;
	vector<bool> used;

	long long cnt_leaves;
	long long cnt_nodes;

	int e3p_feasible = -1;
	int e3p_unfeasible = -1;
};

#endif
