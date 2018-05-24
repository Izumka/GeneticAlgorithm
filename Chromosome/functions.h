//
// Created by oles on 24.05.18.
//

#ifndef CHROMOSOME_FUNCTIONS_H
#define CHROMOSOME_FUNCTIONS_H

#include <vector>
#include <numeric>
#include <random>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

//Vector slicer
typedef std::vector<int>::iterator vec_iter;

vector<int> slicer(vec_iter first, vec_iter last);

void v_merge(vector<int> &x1, const vector<vector<int>> &x2);


#endif //CHROMOSOME_FUNCTIONS_H
