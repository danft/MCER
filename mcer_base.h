#ifndef ISOLVER_H
#define ISOLVER_H

#include "solution.h"
#include "cover.h"
#include "instance.h"
#include "context.h"

#include <vector>

using namespace std;

class MCER_Base {
	public:
		void create_CLS();
		virtual Solution solve() = 0;
		MCER_Base(Context *context);
		~MCER_Base();

	protected:
		double remove_cover(int el, int jcov);
		double apply_cover(int el, int jcov);
		vector<int> get_covered_list();
		
	private: 
		Context *context;
		vector<int> cov_cnt;
		double apply_cover(int el, int jcov, int mul);
		vector<vector<Cover>> covers;
};

#endif
