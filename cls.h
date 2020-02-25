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
	CLS(int n, int m);
	virtual ~CLS();

	virtual void create_cls() = 0;
	const vector<Cover<Instance::mask_size>>& get_cls(int ej);
	void remove_duplicates();


protected:
	bool is_covered(const vector<int> &covl);

	bool is_covered(int ej, const vector<int> &covl);

	void add_cov(const vector<int> &covl);

	void add_cov(int ej, Cover<Instance::mask_size> cov);

	vector<Cover<Instance::mask_size>> get_cls_list(int ej);

	void add_ifnot_covered(const vector<int> &covl);
	void reset();

private:
	STree tree;
	vector<STree> trees;
	vector<bool> has_dup;

	vector<vector<Cover<Instance::mask_size>>> cls_list;
	vector<Cover<Instance::mask_size>> remove_duplicates(vector<Cover<Instance::mask_size>> &c_tmp);

	int n, m;
};

#endif /* CLS_H_ */
