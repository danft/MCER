/*
 * cls_mce.h
 *
 *  Created on: 15 de fev de 2020
 *      Author: danft
 */

#ifndef CLS_MCE_H_
#define CLS_MCE_H_

#include <vector>

using namespace std;

#include "cls.h"
#include "instance.h"

class CLS_MCE : public CLS {
public:
	CLS_MCE(Instance ins);
	virtual ~CLS_MCE();

	void create_cls();

private:
	Instance instance;
	vector<vector<Cover<Instance::mask_size>>> cls_list;

};

#endif /* CLS_MCE_H_ */
