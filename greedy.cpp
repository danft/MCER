#include <vector>

using namespace std;

#include "greedy.h"
#include "cls_mcer.h"
#include "cls.h"

Greedy::Greedy(Context *ctx, CLS *cls_) : MCER_Base(ctx), context(ctx), cls(cls_) {
	used = vector<bool>(context->instance->m, false);
}

Solution Greedy::solve() {

	create_CLS(cls);

	clock_t t1 = clock();
	f();
	context->times.push_back(clock() - t1);

	return Solution(
			context,
			get_opt(),
			1,
			used);
}

void Greedy::f() {

	for (int i = 0; i<context->instance->k; i++) {

		int jbest = 0;
		int ejbest = 0;
		double wbest = -1e15;

		for (int ej = 0; ej < context->instance->m; ej++) if (!used[ej]) {

			for (int j = 0; j<context->cls_list[ej].size(); j++) {

				double w = 0;

				for (int h = 0; h < context->cls_list[ej][j].covl.size(); h++){
					int jpnt = context->cls_list[ej][j].covl[h];

					if (!is_cov(jpnt))
						w += context->instance->wpnt[jpnt];
				}

				w -= context->instance->wel[ej];

				if (w > wbest){
					wbest = w;
					jbest = j;
					ejbest = ej;
				}
			}
		}

		used[ejbest] = true;
		apply_cover(ejbest, jbest);
	}
}
