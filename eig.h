#ifndef EIG_H
#define EIG_H

#include <vector>


struct complex {double re; double im;};   
typedef struct complex complex;

int eig(std::vector<std::vector<complex>> &mat, std::vector<complex> &eig_values);

#endif
