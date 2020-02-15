#ifndef GREEDY_H
#define GREEDY_h

#include "solution.h"
#include "context.h"
#include "mcer_base.h"

class Greedy: public MCER_Base {
	public:
		Solution solve();
		Greedy(Context *context);

	private:
		Context *context;
		vector<bool> used;
		void f();

};

#endif
