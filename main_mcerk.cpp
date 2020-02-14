#include <iostream>

using namespace std;

#include "instance.h"
#include "mcerk.h"
#include "solver_wrapper.h"


int main() {
	//ifstream in("input/AB020.txt");

	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance);

	MCERK mcerk = MCERK(&context);

	solve(mcerk, instance);

	return 0;
}
