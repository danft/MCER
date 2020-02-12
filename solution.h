#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <set>
#include "cover.h"
#include "context.h"

using namespace std;

class Solution {
	public:
	
	string info();
	Solution(Context *context, vector<int> best_sol, vector<clock_t> times, int nsols);

	Solution();

	private:
	void add_to_cover(const Cover &cov);
	Instance instance;
	vector<Cover> opt_cov;
	vector<clock_t> time_ellapsed;
	set<int> cov_set;
	vector<size_t> cls_size;

	int sols_att;
	double sol_val;

};

#endif
