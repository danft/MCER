/*
 * cls.h
 *
 *  Created on: 15 de fev de 2020
 *      Author: danft
 */

#ifndef CLS_H_
#define CLS_H_

#include <vector>

using namespace std;

#include "cover.h"
#include "instance.h"
#include "subset_tree.h"

class CLS {
public:
	CLS(int n);
	virtual ~CLS();

	virtual vector<vector<Cover>> create_cls() = 0;

protected:
	bool is_covered(const vector<int> &covl);
	void add_cov(const vector<int> &covl);
	void add_ifnot_covered(const vector<int> &covl);
	vector<Cover> remove_duplicates(vector<Cover> &c_tmp);
	void reset();

private:
	STree tree;
	int n;

};

#endif /* CLS_H_ */
