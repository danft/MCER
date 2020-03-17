#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <numeric>

#include <iostream>

#include "solution.h"
#include "cover.h"
#include "instance.h"

using namespace std;

Solution::Solution(Context *context, vector<int> opt, long long nleaves, long long nnodes, vector<bool> us) : used(us) {
		instance = *(context->instance);
		opt_cov = vector<Cover<Instance::mask_size>>(instance.m);
		cls_size = vector<size_t>(instance.m);
		cov_set = set<int>();

		e3p_feasible = context->e3p_feasible;
		e3p_unfeasible = context->e3p_unfeasible;

		for (int i = 0; i<context->instance->m; i++) {
			opt_cov[i] = context->cls->get_cls(i)[opt[i]];
			cls_size[i] = context->cls->get_cls(i).size();

			if (used[i])
				add_to_cover(opt_cov[i]);
		}

		this->time_ellapsed = context->times;
		this->cnt_leaves = nleaves;
		this->cnt_nodes = nnodes;
}

Solution::Solution(Context *context, vector<int> opt, long long nleaves, long long nnodes)
: Solution(context, opt, nleaves, nnodes, vector<bool>(context->instance->m, true)){

}

double Solution::get_sol_val() const {
	double sol_val = 0;

	for (auto it: cov_set) {
		sol_val += instance.wpnt[it];
	}

	for (int i = 0; i<instance.m; i++)
		sol_val -= used[i] * instance.wel[i];

	return sol_val;
}

void Solution::add_to_cover(const Cover<Instance::mask_size> &cov) {
	cov_set.insert(cov.covl.begin(), cov.covl.end());
}

string num_str(int x) {
	ostringstream ss;
	ss << "\\num{" << x << "}";
	return ss.str();
}

string num_str(double x, int precision = 1) {
	ostringstream ss;
	ss << setprecision(precision) << fixed << "\\num{" << x << "}";
	return ss.str();
}

string Solution::used_str(string spr) const{
	const string elp[] = {spr, ""};
	ostringstream ss;
	int cnt = 0;
	for (int i = 0; i<instance.m; i++) {
		if (used[i]) {
			cnt++;
			ss << num_str(i+1) << elp[instance.k==cnt];
		}
	}

	return ss.str();
}

string Solution::list() const {
	ostringstream ss;
	ss << num_str(instance.n)<<";" << num_str(instance.m) << ";" <<num_str(instance.k) << ";";
	ss << used_str(",") << ";";
	ss <<setprecision(1) << fixed << num_str(get_sol_val()) << ";";
	//ss << num_str((int)*max_element(cls_size.begin(), cls_size.end())) << ";";

	ss << num_str((int) cls_size[instance.k-1]) << ";";

	if (e3p_feasible >= 0)
		ss << num_str(e3p_feasible + e3p_unfeasible)<< ";";
	ss << num_str((int)cnt_nodes)<< ";" << num_str((int) cnt_leaves) << ";";
	ss <<setprecision(2)<<fixed<< num_str((1.0*time_ellapsed[0]) / CLOCKS_PER_SEC, 2) << ";" <<  num_str((1.0*time_ellapsed[1] + 1.0*time_ellapsed[0]) / CLOCKS_PER_SEC, 2);

	return ss.str();
}

string Solution::table() const{
	const string elp[] = {",", ""};

	ostringstream ss;

	ss << num_str(instance.n) <<" & " << num_str(instance.m) << " & " <<num_str(instance.k)  << " & ";

	ss << used_str(",");

	ss << "&";

	ss <<setprecision(1) << fixed << num_str(get_sol_val()) << " &";

	ss << num_str((int)*max_element(cls_size.begin(), cls_size.end())) << " & ";

	if (e3p_feasible >= 0)
		ss << num_str(e3p_feasible + e3p_unfeasible)<< " & ";

	ss << num_str((int)cnt_nodes)<< " & " << num_str((int) cnt_leaves) << " & ";

	ss <<setprecision(2)<<fixed<< num_str((1.0*time_ellapsed[0]) / CLOCKS_PER_SEC, 2) << "& " <<  num_str((1.0*time_ellapsed[1] + 1.0*time_ellapsed[0]) / CLOCKS_PER_SEC, 2) << "\\\\";

	//ss <<endl;

	return ss.str();
}

string Solution::info(int precision=10) const{
	ostringstream ss;	

	//ss << "Solution: \n";

	//ss << "Ellipses utilized: \n";

	//int cnt = 0;
	/*for (int i = 0; i<instance.m; i++)
		if (used[i]) {
			cnt++;
			ss << "E" << i+1 << ",\n"[cnt==instance.k];
		}
	ss << endl;

	// time ellapsed string 
	for (int i = 0; i<time_ellapsed.size(); i++)
		ss << "Time in Phase " << i+1 << ": " << 1.0 * (time_ellapsed[i]) / CLOCKS_PER_SEC << endl;
	ss << endl;

	ss << "CLS INFO:\n";
	// Size of CLS
	for (int i = 0; i<instance.m; i++) //if (used[i])
		ss << "CLS's size for E_" << i+1 << ": " << cls_size[i] << endl;
	ss << endl;

	ss << "Number of solutions attempted: " << cnt_leaves << endl; 
	ss << "Maximum Cover value:" << get_sol_val() << endl;
	ss << endl;
	
	for (int i = 0; i<instance.m; i++) if (used[i]){
		ss << i+1 << "-th ellipse solution \n";
		ss << "Weight: " << opt_cov[i].w <<" (xc, yc, theta) -> ";

		ss << "(" << opt_cov[i].xc << ", " << opt_cov[i].yc << ", " << opt_cov[i].theta << ")" << endl;
		ss << endl;
	}

	ss << endl;
	*/
	string elp[] = {", ", "]\n"};
	ss << "used=[";
	for (int i = 0; i<instance.m; i++)
		ss << used[i] << elp[i+1==instance.m];
	ss <<endl;

	ss << "sol=[";
	int cnt = 0;

	for (int i = 0; i<instance.m; i++) if (used[i])
	{
		cnt++;
		ss <<setprecision(precision)<<fixed<< "(" << opt_cov[i].xc << ", " << opt_cov[i].yc << ", " << opt_cov[i].theta << ")" << elp[cnt==instance.k];
	}

	ss << endl;

	return ss.str();
}
