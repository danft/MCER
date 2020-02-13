#include "context.h"


Context::Context(const Instance *instance, const vector<vector<Cover>> *covers) : Context(instance) {
	// copies the CLSs
	this->cls_list = *covers;
}

Context::Context(const Instance *instance) {
	this->instance = instance;
	this->cls_list = vector<vector<Cover>>();
	times = vector<clock_t>();
}


void Context::set_covers(const vector<vector<Cover>> *covs) {
	// copies the CLSs
	this->cls_list = *covs;
}
