#include <iostream>

using namespace std;

#include "instance.h"
#include "mcer.h"
#include "solver_wrapper.h"


int main(int argc, char* argv[]) {
	//ifstream in("input/AB090.txt");
	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance, argc, argv);

	MCER mcer = MCER(&context);

	solve(mcer, &context);

	return 0;
}
