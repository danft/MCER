#include <iostream>

using namespace std;

#include "instance.h"
#include "greedy.h"
#include "solver_wrapper.h"


int main() {
	//ifstream in("input/AB090.txt");
	auto instance = read_instance_from_file(cin);

	Context context = Context(&instance);

	Greedy greedy = Greedy(&context);

	solve(greedy, instance);

	return 0;
}
