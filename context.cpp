#include "context.h"


Context::Context(const Instance *instance, const vector<vector<Cover>> *covers) : Context(instance) {
	this->covers = covers;
}

Context::Context(const Instance *instance) {
	this->instance = instance;
	times = vector<clock_t>();
}


void Context::set_covers(const vector<vector<Cover>> *covs) {
	this->covers = covs;
}
