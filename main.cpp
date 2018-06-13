#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <valarray>
#include <thread>
#include <functional>
#include "Chromosome/Chromosome.h"
#include "Population/Populaton.h"

using std::vector;
using namespace std;

double func(vector<int> x){
    return x[0]*x[0];
}

int main(int argc, char* argv[]){
    srand ( time(NULL) );

    double best_fit, worst_fit;
    Populaton population = Populaton(10,10, &func); //HOW TO PASS FUNCTIO
    population.init();
    population.refresh_nofit();
    for (int i = 0; i <10 ; ++i) {

    }{
        population.probabilry_crossover();
        population.probabilry_mutate();
        population.refresh_nofit();
        best_fit = population.best_chromosome.fitness;
        worst_fit = population.worst_chromosome.fitness;

    }
    std::cout << best_fit << std::endl;
    return best_fit;
}