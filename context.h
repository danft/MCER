#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>

using namespace std;

#include "instance.h"
#include "cover.h"


class Context {
	public:
		const Instance *instance;
		const vector<vector<Cover>> *covers;

		Context(const Instance *instance, const vector<vector<Cover>> *covers);
		Context(const Instance *instance);

		void set_covers(const vector<vector<Cover>> *covs);

		vector<clock_t> times;
};

#endif
