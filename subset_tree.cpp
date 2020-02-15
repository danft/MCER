#include <vector>
#include <map>

#include "subset_tree.h"

using namespace std;

Node::Node() {
	ch = map<int, int>();
}


STree::STree(int n) : n(n) {
	root = 0;
	Node r = Node();
	nodes.push_back(r);
	wh = vector<vector<int>>(n, vector<int>());	
}

void STree::add_nodes(const vector<int> &I) {
	int t = root;

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
