/*
 * cls.cpp
 *
 *  Created on: 15 de fev de 2020
 *      Author: danft
 */

#include <algorithm>
#include <vector>

using namespace std;

#include "cls.h"
#include "subset_tree.h"
#include "cover.h"

CLS::CLS(int n): tree(STree(n)){
	// TODO Auto-generated constructor stub
	this->n = n;
}

CLS::~CLS() {
	// TODO Auto-generated destructor stub
}

bool CLS::is_covered(const vector<int> &covl) {
	return tree.has(covl);
}

void CLS::add_cov(const vector<int> &covl) {
	tree.add_nodes(covl);
}

void CLS::add_ifnot_covered(const vector<int> &covl){
	if (!is_covered(covl))
		add_cov(covl);
}

void CLS::reset() {
	tree = STree(n);
}


vector<Cover> CLS::remove_duplicates(vector<Cover> &c_tmp){

	sort(c_tmp.begin(), c_tmp.end(), [](const Cover &ca, const Cover &cb)->bool {return ca.covl.size() > cb.covl.size();});

	STree tree2 = STree(n);
	vector<Cover> ret;

	for (auto c : c_tmp)
	{
		if (!tree2.has(c.covl))
		{
			//cout << l << ": " << c.covl.size() << endl;
			tree2.add_nodes(c.covl);
			ret.push_back(c);
		}
	}

	sort(ret.begin(), ret.end(), [](const Cover &ca, const Cover &cb)->bool {return ca.w > cb.w;});

	return ret;
}
