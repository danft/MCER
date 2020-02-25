#include <iostream>

using namespace std;

#include "instance.h"
#include "greedy.h"
#include "solver_wrapper.h"
#include "cls_mce.h"


int main(int argc, char *argv[]) {
	//ifstream in("input/AB090.txt");
	auto instance = read_instance_from_file(cin);


	CLS_MCE cls = CLS_MCE(instance);
	Context context = Context(&instance, &cls, argc, argv);
	Greedy greedy = Greedy(&context, &cls);

	solve(greedy, &context);

	return 0;
}
