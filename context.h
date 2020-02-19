#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>

using namespace std;

#include "instance.h"
#include "cover.h"
#include "cls_mcer.h"
#include "cls.h"


class Context {
	public:
		const Instance *instance;
		vector<vector<Cover>> cls_list;

		Context(const Instance *instance, const vector<vector<Cover>> *covers);
		Context(const Instance *instance);

		Context(const Instance *instance, int argc, char *argv[]);

		void set_covers(const vector<vector<Cover>> *covs);

		vector<clock_t> times;

		bool print_table = false;
		bool print_info = false;

		int e3p_feasible = 0;
		int e3p_unfeasible = 0;

};

#endif
