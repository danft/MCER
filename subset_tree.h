#ifndef SUBSET_TREE_H
#define SUBSET_TREE_H

#include <vector>
#include <map>

using namespace std;

struct Node {
	map<int, int> ch;
	Node();
};

struct STree {
	int root, n;
	vector<Node> nodes;
	vector<vector<int>> wh;
	STree(int n) ;
	void add_nodes(vector<int> &I) ;
	bool has(vector<int> &I) ;
	bool _has(vector<int> &I, int k, int t);
};


#endif
