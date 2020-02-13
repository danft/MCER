#include <iostream>

using namespace std;

#include "instance.h"
#include "mcer.h"
#include "solver_wrapper.h"


int main() {

	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance);

	MCER mcer = MCER(&context);

	solve(mcer, instance);

	return 0;
}
