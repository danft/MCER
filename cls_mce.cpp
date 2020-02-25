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
#include "instance.h"

CLS_MCE::CLS_MCE(Instance ins): instance(ins), CLS(ins.n, ins.m) {
	// TODO Auto-generated constructor stub
}

CLS_MCE::~CLS_MCE() {
	// TODO Auto-generated destructor stub
}

void CLS_MCE::create_cls() {
	int n = instance.n;
	for (int l = 0; l<instance.m; ++l) {
		//reset();
		double a = instance.a[l];
		double b = instance.b[l];

		for (int i = 0; i<n; i++){
			auto cov = Cover<Instance::mask_size>(instance, l, instance.X[i], instance.Y[i], 0);
			add_cov(l, cov);

			for (int j = i+1; j<n; j++) {
				vector<pair<double, Point>> sols = e2p(a, b, instance.X[i], instance.X[j], instance.Y[i], instance.Y[j], false);

				for (int h = 0; h<sols.size(); h++) {
					cov = Cover<Instance::mask_size>(instance, l, sols[h].second.x, sols[h].second.y, sols[h].first);
					add_cov(l, cov);
				}
			}
		}
	}
}
