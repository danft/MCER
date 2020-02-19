#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <set>
#include "cover.h"
#include "context.h"

using namespace std;

class Solution {
	public:
	
	string info() const;
	string table() const;

	Solution(Context *context, vector<int> opt, long long nsols);
	Solution(Context *context, vector<int> opt, long long nsols, vector<bool> used);

	Solution();

	private:
	void add_to_cover(const Cover &cov);
	Instance instance;
	vector<Cover> opt_cov;
	vector<clock_t> time_ellapsed;
	set<int> cov_set;
	vector<size_t> cls_size;
	vector<bool> used;

	long long sols_att;
	double sol_val;

	int e3p_feasible = 0;
	int e3p_unfeasible = 0;
};

#endif
