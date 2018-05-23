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

void func(int i, int& res){
//    for (int j = 0; j < 100; j++) {
//        std::cout << "index: " << i << std::endl;
//    }

    res = i+2;
}

int main() {
    vector<std::thread> threads;
    vector<int> results{2};

    for (int i = 0; i < 2; i++) {
        threads.push_back(std::thread(func, i, results[i]));
    }

    for (int i = 0; i < 2; i++) {
        threads[i].join();
    }

    for (int i = 0; i < 2; i++) {
        cout << results[i] << endl;
    }

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