#ifndef CLS_MCER_H
#define CLS_MCER_H

#include <vector>
#include "cover.h"
#include "cls.h"
#include "instance.h"

using namespace std;

//vector<vector<Cover>> CLS_MCER(Instance instance);

class CLS_MCER : public CLS {
public:
	CLS_MCER(Instance ins);
	void create_cls();
	int get_e3p_feasible() const;
	int get_e3p_unfeasible() const;
private:
	Instance instance;
	int e3p_feasible = 0;
	int e3p_unfeasible = 0;
};

#endif
