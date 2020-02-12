#include <vector>
#include <set>
#include <iostream>

using namespace std;

#include "cls_mcer.h"
#include "mcer_base.h"
#include "instance.h"

MCER_Base::MCER_Base(Context *context) : context(context) {
	cov_cnt = vector<int>(context->instance->m, 0);
}

MCER_Base::~MCER_Base() {
	//delete context->covers;
}

void MCER_Base::create_CLS() {
	clock_t t1 = clock();
	covers = CLS_MCER(*(context->instance));
	context->set_covers(&covers);
	context->times.push_back(clock() - t1);
}

double MCER_Base::apply_cover(int el, int jcov) {
	return apply_cover(el, jcov, 1);
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

	for (int i = 0; i<covers[el][jcov].covl.size(); i++) 
	{
		int jpnt = covers[el][jcov].covl[i];
		wret += context->instance->wpnt[jpnt] * (cov_cnt[jpnt] == cmp);
		cov_cnt[jpnt] += mul;
	}

	return wret;
}

double MCER_Base::remove_cover(int el, int jcov) {
	return apply_cover(el, jcov, -1);
}
