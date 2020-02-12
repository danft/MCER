#include <sstream>
#include <vector>
#include <set>

#include "solution.h"
#include "cover.h"

using namespace std;

Solution::Solution(Context *context, vector<int> best_sol, vector<clock_t> times, int nsols){

	instance = *(context->instance);
	opt_cov = vector<Cover>(instance.m);
	cls_size = vector<size_t>(instance.m);
	cov_set = set<int>();

	for (int i = 0; i<context->instance->m; i++) 
	{
		opt_cov[i] = (*context->covers)[i][best_sol[i]];
		cls_size[i] = (*context->covers)[i].size();
		add_to_cover(opt_cov[i]);
	}

	this->time_ellapsed = times;
	this->sols_att = nsols;
}

void Solution::add_to_cover(const Cover &cov) {
	cov_set.insert(cov.covl.begin(), cov.covl.end());

	sol_val = 0;

	for (auto it: cov_set)
		sol_val += instance.wpnt[it];
}

string Solution::info() {
	ostringstream ss;	
	ss << "Solution: \n";

	// time ellapsed string 
	for (int i = 1; i<time_ellapsed.size(); i++)
		ss << "Time in Phase " << i << ": " << 1.0 * (time_ellapsed[i]-time_ellapsed[i-1]) / CLOCKS_PER_SEC << endl;
	ss << endl;

	// Size of CLS
	for (int i = 0; i<instance.m; i++)
		ss << "CLS's size for E_" << i+1 << ": " << cls_size[i] << endl;
	ss << endl;

	ss << "Number of solutions attempted: " << sols_att << endl; 
	ss << "Maximum Cover value:" << sol_val << endl;
	ss << endl;
	
	for (int i = 0; i<instance.m; i++) {
		ss << i+1 << "-th ellipse solution \n";
		ss << "Weight: " << opt_cov[i].w <<" (xc, yc, theta) -> ";

		ss << "(" << opt_cov[i].xc << ", " << opt_cov[i].yc << ", " << opt_cov[i].theta << ")" << endl;
		ss << endl;
	}

	ss << endl;
	
	string elp[] = {", ", "]\n"};
	ss << "sol=[";

	for (int i = 0; i<instance.m; i++) 
	{
		ss <<fixed<< "(" << opt_cov[i].xc << ", " << opt_cov[i].yc << ", " << opt_cov[i].theta << ")" << elp[i==instance.m-1];
	}

	ss << endl;

	return ss.str();
}
