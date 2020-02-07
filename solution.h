#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include "cover.h"

using namespace std;

struct Solution {
	Instance instance;
	vector<int> cov_cnt;
	vector<int> best_cov;
	vector<vector<Cover>> covers;
	vector<clock_t> time_ellapsed;
	int sols_att;
	double sol_val;

	string info();
	Solution(Instance ins, vector<vector<Cover>> cov, vector<int> best_cov, vector<int> cov_cnt, vector<clock_t> tell, int sols_att, double sol_val);
	Solution();
};

#endif
