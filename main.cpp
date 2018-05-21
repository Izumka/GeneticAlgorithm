#include <iostream>
#include <chromosome.h>
#include <population.h>
#include <vector>
#include <valarray>
#include "population.h"

using namespace std;

int main() {

//    Population population = new Population(genes_length=5, num_type="int", fitness_fun=fit, size=10);
//
//    double arr[5] = {1,1,1,2,3};


    return EXIT_SUCCESS;
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