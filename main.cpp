#include <iostream>

#include <random>
#include <vector>
#include <algorithm>
#include <valarray>
#include <thread>
//#include "chromosome.h"
//#include "population.h"

using std::vector;
using namespace std;


int main() {

    return 0;
}

double fit(vector<int>& lst){
    int size = lst.size();

    valarray<double> arr_for_sum(size);

    for(int i = 0; i < size; i++){
        double num;
        num = ((i + 1)/ size) * lst[i];
        arr_for_sum[i] = num;
    }

    return arr_for_sum.sum();
}