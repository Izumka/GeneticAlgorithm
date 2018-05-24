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
    std::cout << "lets" << std::endl;

    int size = lst.size();

    valarray<double> arr_for_sum(size);

    for(int i = 0; i < size; i++){
        double num;
        num = ((i + 1)/ size) * lst[i];
        arr_for_sum[i] = num;
    }

    return arr_for_sum.sum();
}

void print_vector(std::vector<Chromosome> vector){
    string string1 = "{";

    for (Chromosome chromosome : vector ) {
        string1 += chromosome.getFitness();
}
    string1 += "}";


}

int main(){

    Population population = Population(5,0,fitnes_func,10);
    population.generate_init();
    cout << "sadads"<< endl;
    print_vector(population.getPopulation_set());
    population.refresh_nofit();
    print_vector(population.getPopulation_set());
    cout << ""<< endl;
    cout << "sldkf"<< endl;

    while(true){
        population.prob_crossover();
        print_vector(population.getPopulation_set());
        population.prob_mutation();
        print_vector(population.getPopulation_set());
        population.refresh_nofit();
        print_vector(population.getPopulation_set());
        double best = population.getBest_fit();
        double worst = population.getWorst_fit();
        if(best/worst < 0.005){
            break;
        }
    }

    return 0;
}
