#include <vector>
#include <set>
#include <iostream>

using namespace std;

#include "cls_mcer.h"
#include "mcer_base.h"
#include "instance.h"

MCER_Base::MCER_Base(Context *context) : context(context) {
	cov_cnt = vector<int>(context->instance->m, 0);
	curr = vector<int>(context->instance->m, 0);
}

MCER_Base::~MCER_Base(){

}

void MCER_Base::create_CLS() {
	clock_t t1 = clock();
	auto covers = CLS_MCER(*(context->instance));
	context->set_covers(&covers);
	context->times.push_back(clock() - t1);
}

vector<int> MCER_Base::get_curr() {
	return curr;
}

double MCER_Base::apply_cover(int el, int jcov) {
	return apply_cover(el, jcov, 1);
}

bool MCER_Base::covers_any(bitset<100> mask, const Cover &cov) {
	return !((cov.mask | mask) == mask);
}

vector<int> MCER_Base::get_covered_list() {
	vector<int> ret;

	for (int i = 0; i<context->instance->n; i++)
		if (cov_cnt[i] > 0)
			ret.push_back(i);

	return ret;
}

double MCER_Base::apply_cover(int el, int jcov, int mul) {
	double wret = 0;

	int cmp = (mul>0) ? 0 : 1;
	curr[el] = jcov;

	for (int i = 0; i<context->cls_list[el][jcov].covl.size(); i++)
	{
		int jpnt = context->cls_list[el][jcov].covl[i];
		wret += context->instance->wpnt[jpnt] * (cov_cnt[jpnt] == cmp);
		cov_cnt[jpnt] += mul;
	}

	return wret;
}

double MCER_Base::remove_cover(int el, int jcov) {
	double ret = apply_cover(el, jcov, -1);
	curr[el] = 0;
	return ret;
}