#ifndef ISOLVER_H
#define ISOLVER_H

#include "solution.h"
#include "cover.h"
#include "instance.h"
#include "context.h"
#include "cls.h"

#include <vector>
#include <unordered_set>

using namespace std;

class MCER_Base {
	public:
		void create_CLS(CLS *cls);
		virtual Solution solve() = 0;
		virtual ~MCER_Base();
		MCER_Base(Context *context);

	protected:
		double remove_cover(int el, int jcov);
		double apply_cover(int el, int jcov);

		void set_opt();
		vector<int> get_opt();
		bool covers_any(bitset<Instance::mask_size> mask, const Cover<Instance::mask_size> & cov);
		bool is_cov(int i);
		
		bool is_seen(int ej, bitset<Instance::mask_size> mask);
		void add_seen(int ej, bitset<Instance::mask_size> mask);
		void clear_seen();

	private: 
		Context *context;
		vector<int> cov_cnt;
		vector<int> curr;
		vector<int> opt;
		vector<unordered_set<bitset<Instance::mask_size>>> seen;
		double apply_cover(int el, int jcov, int mul);
};

#endif
