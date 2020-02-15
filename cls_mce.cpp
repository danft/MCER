/*
 * cls_mce.cpp
 *
 *  Created on: 15 de fev de 2020
 *      Author: danft
 */
#include <vector>
#include <algorithm>

using namespace std;

#include "cls_mce.h"
#include "cover.h"
#include "utils.h"
#include "e2p/e2p.h"

CLS_MCE::CLS_MCE(Instance ins): instance(ins), CLS(ins.n) {
	// TODO Auto-generated constructor stub
}

CLS_MCE::~CLS_MCE() {
	// TODO Auto-generated destructor stub
}

vector<vector<Cover>> CLS_MCE::create_cls() {
	int n = instance.n;
	auto covs = vector<vector<Cover>>(instance.m);

	for (int l = 0; l<instance.m; ++l) {
		reset();
		double a = instance.a[l];
		double b = instance.b[l];
		vector<Cover> c_tmp;


		for (int i = 0; i<n; i++){
			Cover cov = Cover(instance, l, instance.X[i], instance.Y[i], 0);

			if (!is_covered(cov.covl)) {
				c_tmp.push_back(cov);
				add_cov(cov.covl);
			}

			for (int j = i+1; j<n; j++) {
				vector<pair<double, Point>> sols = e2p(a, b, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j], false);

				for (int h = 0; h<sols.size(); h++) {
					cov = Cover(instance, l, sols[h].second.x, sols[h].second.y, sols[h].first);

					if (!is_covered(cov.covl)) {
						c_tmp.push_back(cov);
						add_cov(cov.covl);
					}
				}
			}
		}

		covs[l] = remove_duplicates(c_tmp);
	}

	return covs;
}
