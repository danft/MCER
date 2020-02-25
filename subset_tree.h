#ifndef SUBSET_TREE_H
#define SUBSET_TREE_H

#include <vector>
#include <map>

using namespace std;

struct Node {
	map<int, int> ch;
	int index;
	Node();
	Node(int in);
};

struct STree {
	int root, n;
	vector<Node> nodes;
	vector<vector<int>> wh;
	STree(int n) ;
	void add_nodes(const vector<int> &I, int index);
	bool has(const vector<int> &I);
	bool _has(const vector<int> &I, int k, int t);

	vector<int> leaves; // index of leaves
};


#endif
