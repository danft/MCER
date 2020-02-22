#include "context.h"
#include "cls_mcer.h"
#include "cls.h"
#include <cstring>
#include <iostream>

using namespace std;

Context::Context(const Instance *instance, const vector<vector<Cover>> *covers) : Context(instance) {
	// copies the CLSs
	this->cls_list = *covers;
}

Context::Context(const Instance *instance) {
	this->instance = instance;
	this->cls_list = vector<vector<Cover>>();
	times = vector<clock_t>();
}

Context::Context(const Instance *instance, int argc, char *argv[]) : Context(instance){
	for (int i = 1; i<argc; ++i) {

		if (strcmp(argv[i], "--print-table") == 0)
			print_table = true;

		if (strcmp(argv[i], "--print-info") == 0)
			print_info = true;

		if (strcmp(argv[i], "--print-list") == 0)
			print_list = true;
	}

	if (!print_table && !print_info && !print_list)
		print_info = true;
}


void Context::set_covers(const vector<vector<Cover>> *covs) {
	// copies the CLSs
	this->cls_list = *covs;
}
