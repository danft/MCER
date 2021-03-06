#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

#include "cls_mcer.h"
#include "subset_tree.h"
#include "e2p/e2p.h"
#include "e3p/e3p.h"

#include "utils.h"

using namespace std;

bool check1(double a, double x1, double x2, double y1, double y2) {
	Point p1 = Point(x1, y1);
	Point p2 = Point(x2, y2);

	return (p1.dist(p2) - 1e-9 < 2 * a);
}

bool check2(double a, double b, double x1, double x2, double x3, double y1, double y2, double y3){
	Point p1 = Point(x1, y1);
	Point p2 = Point(x2, y2);
	Point p3 = Point(x3, y3);

	double area = triangle_area(p1, p2, p3);

	return (area - 1e-9 < 3 * a * b * sqrt(3)/4);
	return area - 1e-9 < acos(-1) * a * b;
}

CLS_MCER::CLS_MCER(Instance ins): instance(ins), CLS(ins.n, ins.m){
}

void add_to_set(set<tuple<int,int,int>> &skip, int i, int j, int k){
	vector<int> tm(3);
	tm[0] = i; tm[1] = j; tm[2] = k;
	sort(tm.begin(), tm.end());
	skip.insert(make_tuple(tm[0], tm[1], tm[2]));
}

void CLS_MCER::create_cls() {

	int cnt_e3p = 0;

	for (int l = 0; l<instance.m; ++l) {
		set<tuple<int,int,int>> skip;

		reset();

		double a = instance.a[l];
		double b = instance.b[l];

		vector<Cover<Instance::mask_size>> c_tmp;

		for (int i = 0; i<instance.n; i++) {
			auto cov = Cover<Instance::mask_size>(instance, l, instance.X[i], instance.Y[i], 0);

			add_cov(l, cov);

			for (int j = i+1; j<instance.n; ++j) {
				
				if (!check1(a, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j])) continue;

				vector<pair<double, Point>> sols = e2p(a, b, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j]);

				for (int h = 0; h<sols.size(); h++) {
					cov = Cover<Instance::mask_size>(instance, l, sols[h].second.x, sols[h].second.y, sols[h].first);

					add_cov(l, cov);
				}

				for (int k = j+1; k < instance.n; ++k)
				{
					if (skip.count(make_tuple(i, j, k))) continue;
					if (!check1(a, instance.X[j], instance.X[k], instance.Y[j], instance.Y[k])) continue;
					if (!check2(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k])) continue;

					//cout << l << " -> " << i <<", " << j <<", " << k << endl;
					cnt_e3p++;
					sols = e3p(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k]);
					e3p_feasible += sols.size() > 0;
					e3p_unfeasible += sols.size() == 0;
					for (int h = 0; h < sols.size(); h++) {
						cov = Cover<Instance::mask_size>(instance, l, sols[h].second.x, sols[h].second.y, sols[h].first);

						for (int p : cov.covl){
							add_to_set(skip, i, j, p);
							add_to_set(skip, i, k, p);
							add_to_set(skip, j, k, p);
						}

						add_cov(l, cov);
					}
				}
			}
		}
	}
}

int CLS_MCER::get_e3p_feasible() const {
	return e3p_feasible;
}

int CLS_MCER::get_e3p_unfeasible() const {
	return e3p_unfeasible;
}
