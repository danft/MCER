#include "cls_mcer.h"
#include "subset_tree.h"
#include "e2p.h"
#include "e3p.h"
#include <vector>
#include <algorithm>

vector<vector<Cover>> CLS_MCER(Instance instance) {

	auto covs = vector<vector<Cover>>(instance.m);

	for (int l = 0; l<instance.m; ++l) {
		double a = instance.a[l];
		double b = instance.b[l];
		STree tree = STree(instance.n);

		vector<Cover> c_tmp;

		for (int i = 0; i<instance.n; i++) {
			Cover cov = Cover(instance, l, 0, instance.X[i], instance.Y[i]);

			if (!tree.has(cov.covl)) {
				c_tmp.push_back(cov);
				tree.add_nodes(cov.covl);
			}

			for (int j = i+1; j<instance.n; ++j) {
				
				vector<pair<double, Point>> sols = e2p(a, b, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j]);

				for (int h = 0; h<sols.size(); h++) {
					cov = Cover(instance, l, sols[h].first, sols[h].second.x, sols[h].second.y);

					if (!tree.has(cov.covl))
					{
						c_tmp.push_back(cov);
						tree.add_nodes(cov.covl);
					}
				}

				for (int k = j+1; k < instance.n; ++k)
				{
					sols = e3p(a, b, instance.X[i], instance.X[j], instance.X[k], instance.Y[i], instance.Y[j], instance.Y[k]);

					for (int h = 0; h < sols.size(); h++) {
						cov = Cover(instance, l, sols[h].first, sols[h].second.x, sols[h].second.y);

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

	return covs;
}
