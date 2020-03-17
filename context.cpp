#include "context.h"
#include "cls_mcer.h"
#include "cls.h"
#include <cstring>
#include <iostream>

using namespace std;

Context::Context(Instance *instance, CLS *_cls) {
	this->instance = instance;
	this->cls = _cls;
	times = vector<clock_t>();
}

Context::Context(Instance *instance, CLS *_cls, int argc, char *argv[]) : Context(instance, _cls){
	for (int i = 1; i<argc; ++i) {

		if (strcmp(argv[i], "--print-table") == 0)
			print_table = true;

		if (strcmp(argv[i], "--print-info") == 0)
			print_info = true;

		if (strcmp(argv[i], "--print-list") == 0)
			print_list = true;

		if (strcmp(argv[i], "--precision") == 0){
			if (i+1 < argc)
				precision = stoi(argv[i+1]);
			instance->precision = precision;
		}
	}

	if (!print_table && !print_info && !print_list)
		print_info = true;
}
