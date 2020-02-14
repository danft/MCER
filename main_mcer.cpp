#include <iostream>

using namespace std;

#include "instance.h"
#include "mcer.h"
#include "solver_wrapper.h"


int main() {
	//ifstream in("input/AB090.txt");
	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance);

	MCER mcer = MCER(&context);

	solve(mcer, instance);

	return 0;
}
