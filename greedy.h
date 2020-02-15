#ifndef GREEDY_H
#define GREEDY_h

#include "solution.h"
#include "context.h"
#include "mcer_base.h"
#include "cls.h"

class Greedy: public MCER_Base {
	public:
		Solution solve();
		Greedy(Context *context, CLS *cls);

	private:
		Context *context;
		vector<bool> used;
		CLS *cls;
		void f();

};

#endif
