#include <iostream>

using namespace std;

#include "instance.h"
#include "mcerk.h"
#include "solver_wrapper.h"
#include "cls.h"
#include "cls_mce.h"


int main() {
	//ifstream in("input/AB020.txt");

	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance);
	CLS_MCE cls = CLS_MCE(instance);

	MCERK mcerk = MCERK(&context, &cls);

	solve(mcerk, instance);

	return 0;
}
