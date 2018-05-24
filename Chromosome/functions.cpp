//
// Created by oles on 24.05.18.
//

#include "functions.h"

#include <vector>
#include <numeric>
#include <random>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

//Vector slicer
typedef std::vector<int>::iterator vec_iter;

vector<int> slicer(vec_iter first, vec_iter last) {
    vector<int> fin;
    for (vec_iter cur = first; cur != last; ++cur) {
        cout<<*cur<<endl;
        fin.push_back(*cur);
    }
    return fin;
}

void v_merge(vector<int> &x1, const vector<vector<int>> &x2) {
    for (int v = 0; v < x2.size(); v++) {
        for (int i = 0; i < x2[v].size(); i++) {
            x1.push_back(x2[v][i]);
        }
    }
}