#include <vector>
#include <set>
#include <iostream>

using namespace std;

//#include "cls_mcer.h"
#include "mcer_base.h"
#include "instance.h"
#include "cls.h"
#include "cls_mcer.h"

MCER_Base::MCER_Base(Context *context) : context(context) {
	cov_cnt = vector<int>(context->instance->n, 0);
	curr = vector<int>(context->instance->m, 0);
	opt = vector<int>(context->instance->m, 0);
}

MCER_Base::~MCER_Base(){

}

void MCER_Base::create_CLS(CLS* cls) {
	clock_t t1 = clock();
	cls->create_cls();
	cls->remove_duplicates();
	context->times.push_back(clock() - t1);

	CLS_MCER *cls2 = dynamic_cast<CLS_MCER*>(cls);
	if (cls2 != NULL){
		context->e3p_feasible = cls2->get_e3p_feasible();
		context->e3p_unfeasible = cls2->get_e3p_unfeasible();
	}
}

bool MCER_Base::is_cov(int i) {
	return cov_cnt[i] > 0;
}

void MCER_Base::set_opt(){
	for (int i = 0; i<context->instance->m; i++)
		opt[i] = curr[i];
}

vector<int> MCER_Base::get_opt(){
	return opt;
}

double MCER_Base::apply_cover(int el, int jcov) {
	return apply_cover(el, jcov, 1);
}

bool MCER_Base::covers_any(bitset<Instance::mask_size> mask, const Cover<Instance::mask_size> &cov) {
	return !((cov.mask | mask) == mask);
}

double MCER_Base::apply_cover(int el, int jcov, int mul) {
	double wret = 0;

	int cmp = (mul>0) ? 0 : 1;
	curr[el] = jcov;

	for (int i = 0; i<context->cls->get_cls(el)[jcov].covl.size(); i++)
	{
		int jpnt = context->cls->get_cls(el)[jcov].covl[i];
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
