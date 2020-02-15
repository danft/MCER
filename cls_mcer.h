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
	CLS_MCER(Instance instance);
	vector<vector<Cover>> create_cls();
private:
	Instance instance;
};

#endif
