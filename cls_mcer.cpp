#include <vector>
#include <algorithm>
#include <iostream>
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

	return area - 1e-9 < acos(-1) * a * b;
}

vector<vector<Cover>> CLS_MCER(Instance instance) {

	auto covs = vector<vector<Cover>>(instance.m);
	int cnt_e3p = 0;
	for (int l = 0; l<instance.m; ++l) {
		double a = instance.a[l];
		double b = instance.b[l];
		STree tree = STree(instance.n);

		vector<Cover> c_tmp;

		for (int i = 0; i<instance.n; i++) {
			Cover cov = Cover(instance, l, instance.X[i], instance.Y[i], 0);

			if (!tree.has(cov.covl)) {
				c_tmp.push_back(cov);
				tree.add_nodes(cov.covl);
			}

			for (int j = i+1; j<instance.n; ++j) {
				
				if (!check1(a, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j])) continue;

				vector<pair<double, Point>> sols = e2p(a, b, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j]);

				for (int h = 0; h<sols.size(); h++) {
					cov = Cover(instance, l, sols[h].second.x, sols[h].second.y, sols[h].first);

					if (!tree.has(cov.covl))
					{
						c_tmp.push_back(cov);
						tree.add_nodes(cov.covl);
					}
				}

				for (int k = j+1; k < instance.n; ++k)
				{
					if (!check1(a, instance.X[j], instance.X[k], instance.Y[j], instance.Y[k])) continue;
					if (!check2(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k])) continue;

					cnt_e3p++;
					sols = e3p(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k]);

					for (int h = 0; h < sols.size(); h++) {
						cov = Cover(instance, l, sols[h].second.x, sols[h].second.y, sols[h].first);

						if (!tree.has(cov.covl))
						{
							c_tmp.push_back(cov);
							tree.add_nodes(cov.covl);
						}
					}
				}
			}
		}

		sort(c_tmp.begin(), c_tmp.end(), [](const Cover &ca, const Cover &cb)->bool {return ca.covl.size() > cb.covl.size();});

		STree tree2 = STree(instance.n);


		for (auto c : c_tmp) 
		{
			if (!tree2.has(c.covl)) 
			{
				//cout << l << ": " << c.covl.size() << endl;
				tree2.add_nodes(c.covl);
				covs[l].push_back(c);
			}
		}

		sort(covs[l].begin(), covs[l].end(), [](const Cover &ca, const Cover &cb)->bool {return ca.w > cb.w;});
	}

	cout << "Number of times E3P was called: " << cnt_e3p << endl;
	return covs;
}
