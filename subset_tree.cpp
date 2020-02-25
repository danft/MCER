#include <vector>
#include <map>

#include "subset_tree.h"

using namespace std;

Node::Node() {
	ch = map<int, int>();
	index = -1;
}

Node::Node(int in):Node(){
	index=in;
}


STree::STree(int n) : n(n) {
	root = 0;
	Node r = Node();
	nodes.push_back(r);
	wh = vector<vector<int>>(n, vector<int>());	
}

void STree::add_nodes(const vector<int> &I, int index) {
	int t = root;

	int leave_index=-1;

	for (int u : I) {

		int nxt = nodes[t].ch[u];
		if (nxt == 0) {
			nxt = nodes.size();
			Node nno = Node();
			nodes.push_back(nno);
			wh[u].push_back(nxt);
		}

		nodes[t].ch[u] = nxt;
		t = nxt;

		if (nodes[t].ch.size() == 0 && leave_index==-1)
			leave_index = nodes[t].index;
	}

	//is it a leaf?
	if (nodes[t].ch.size() == 0) {
		if (leave_index == -1){
			leave_index = leaves.size();
			leaves.push_back(index);
		}

		leaves[leave_index] = index;
		nodes[t].index = leave_index;
	}
}

bool STree::has(const vector<int> &I) {
	if (I.size() == 0) return true;

	for (int t : wh[I[0]])
		if (_has(I, 1, t)) return true;

	return false;
}

bool STree::_has(const vector<int> &I, int k, int t) {
	if (k == I.size()) return true;

	for (auto ut : nodes[t].ch) {
		int	u = ut.first;

		if (u > I[k]) return false;

		if (u == I[k])
			return _has(I, k+1, nodes[t].ch[u]);

		if (_has(I, k, nodes[t].ch[u])) return true;
	}

	return false;
}
