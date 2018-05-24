#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <valarray>
#include <thread>
#include "Chromosome/chromosome.h"
#include "Population/population.h"

using std::vector;
using namespace std;


int fitnes_func(vector<int> lst){
    int size = lst.size();

    valarray<double> arr_for_sum(size);

    for(int i = 0; i < size; i++){
        double num;
        num = ((i + 1)/ size) * lst[i];
        arr_for_sum[i] = num;
    }

    return arr_for_sum.sum();
}

int main(){

    Population population = Population(5,0,fitnes_func,10);

    population.generate_init();
    population.refresh_nofit();

    while(true){
        population.prob_crossover();
        population.prob_mutation();
        population.refresh_nofit();
        double best = population.getBest_fit();
        double worst = population.getWorst_fit();
        if(best/worst < 0.005){
            break;
        }
    }

    return 0;
}
