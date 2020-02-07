#ifndef ISOLVER_H
#define ISOLVER_H

#include "solution.h"

struct ISolver {
	virtual Solution solve() = 0;
};

#endif
