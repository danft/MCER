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
		CLS *cls;

		//Context(const Instance *instance, CLS *cls);
		Context(const Instance *instance, CLS *cls);

		Context(const Instance *instance, CLS *cls, int argc, char *argv[]);

		vector<clock_t> times;

		//const vector<Cover<Instance::mask_size>>& get_cls(int ej);
		bool print_table = false;
		bool print_info = false;
		bool print_list = false;

		int e3p_feasible = -1;
		int e3p_unfeasible = -1;

};

#endif
