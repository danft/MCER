#include <sstream>
#include <vector>

#include "solution.h"
#include "cover.h"

using namespace std;

Solution::Solution(Instance ins, vector<vector<Cover>> cov, vector<int> best_cov, vector<int> cov_cnt, vector<clock_t> tell, int sols_att, double sol_val){
	this->instance = ins;
	this->covers = cov;
	this->best_cov = best_cov;
	this->cov_cnt = cov_cnt;
	this->time_ellapsed = tell;
	this->sols_att = sols_att;
	this->sol_val = sol_val;
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
		ss << "CLS's size for E_" << i+1 << ": " << covers[i].size() << endl;
	ss << endl;

	ss << "Number of solutions attempted: " << sols_att << endl; 
	ss << "Maximum Cover value:" << sol_val << endl;
	ss << endl;
	
	for (int i = 0; i<instance.m; i++) {
		int j = best_cov[i];

		ss << i+1 << "-th ellipse solution \n";
		ss << "Weight: " << covers[i][j].w <<" (xc, yc, theta) -> ";

		ss << "(" << covers[i][j].xc << ", " << covers[i][j].yc << ", " << covers[i][j].theta << ")" << endl;
		ss << endl;
	}

	ss << endl;
	
	string elp[] = {", ", "]\n"};
	ss << "sol=[";

	for (int i = 0; i<instance.m; i++) 
	{
		int j = best_cov[i];
		ss <<fixed<< "(" << covers[i][j].xc << ", " << covers[i][j].yc << ", " << covers[i][j].theta << ")" << elp[i==instance.m-1];
	}

	ss << endl;

	return ss.str();
}
