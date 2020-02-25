/*
 * cls.cpp
 *
 *  Created on: 15 de fev de 2020
 *      Author: danft
 */

#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#include "cls.h"
#include "subset_tree.h"
#include "cover.h"
#include "instance.h"

CLS::CLS(int n, int m): tree(STree(n)){
	// TODO Auto-generated constructor stub
	trees = vector<STree>(m, STree(n));
	cls_list = vector<vector<Cover<Instance::mask_size>>>(
			m, vector<Cover<Instance::mask_size>>());
	this->n = n;
	this->m = m;
	has_dup = vector<bool>(m, true);
}

CLS::~CLS() {
	// TODO Auto-generated destructor stub
}

bool CLS::is_covered(const vector<int> &covl) {
	return tree.has(covl);
}

bool CLS::is_covered(int ej, const vector<int> &covl) {
	return trees[ej].has(covl);
}

void CLS::add_cov(int ej, Cover<Instance::mask_size> cov) {
	if (trees[ej].has(cov.covl)) return;

	trees[ej].add_nodes(cov.covl, cls_list[ej].size());

	cls_list[ej].push_back(cov);
}

const vector<Cover<Instance::mask_size>>& CLS::get_cls(int ej){
	return cls_list[ej];
}


vector<Cover<Instance::mask_size>> CLS::get_cls_list(int ej){
	auto cls = vector<Cover<Instance::mask_size>>();

	for (int i = 0; i<trees[ej].leaves.size(); i++){
		int j = trees[ej].leaves[i];
		cls.push_back(cls_list[ej][j]);
	}

	return remove_duplicates(cls);
}


void CLS::add_cov(const vector<int> &covl) {
	tree.add_nodes(covl, 0);
}

void CLS::add_ifnot_covered(const vector<int> &covl){
	if (!is_covered(covl))
		add_cov(covl);
}

void CLS::reset() {
	tree = STree(n);
}

void CLS::remove_duplicates(){
	for (int i = 0; i<m; i++)
		cls_list[i] = remove_duplicates(cls_list[i]);
}

vector<Cover<Instance::mask_size>> CLS::remove_duplicates(vector<Cover<Instance::mask_size>> &c_tmp){

	sort(c_tmp.begin(), c_tmp.end(), [](const Cover<Instance::mask_size> &ca, const Cover<Instance::mask_size> &cb)->bool {return ca.covl.size() > cb.covl.size();});

	STree tree2 = STree(n);
	vector<Cover<Instance::mask_size>> ret;

	for (auto c : c_tmp)
	{
		if (!tree2.has(c.covl))
		{
			tree2.add_nodes(c.covl, 0);
			ret.push_back(c);
		}
	}

	sort(ret.begin(), ret.end(), [](const Cover<Instance::mask_size> &ca, const Cover<Instance::mask_size> &cb)->bool {return ca.w > cb.w;});

	return ret;
}
