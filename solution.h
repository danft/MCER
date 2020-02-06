#ifndef SOLUTION_H
#define SOLUTION_H

struct Solution {
	Instance instance;
	vector<int> cov_cnt;
	vector<Cover> cov;
	clock_t t1 = 0, t2 = 0, t3 = 0, t4 = 0;

	string to_string();

	Solution(vector<cover> &cov, vector<int> &cov_cnt): cov(cov), cov_cnt(cov_cnt) {}
};

#endif
