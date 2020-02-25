#include <iostream>

using namespace std;

#include "instance.h"
#include "mcerk.h"
#include "solver_wrapper.h"
#include "cls.h"
#include "cls_mcer.h"


int main(int argc, char *argv[]) {
	//ifstream in("input/AB020.txt");

	auto instance = read_instance_from_file(cin);

	CLS_MCER cls = CLS_MCER(instance);
	Context context = Context(&instance, &cls, argc, argv);


	MCERK mcerk = MCERK(&context, &cls);

	solve(mcerk, &context);

	return 0;
}
