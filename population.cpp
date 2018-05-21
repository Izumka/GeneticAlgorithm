#include "chromosome.h"
#include "population.h"
#include <string>
#include <vector>
#include <valarray>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

template<typename n_type, typename f_type>

void Population<n_type, f_type>::generate_subset(int size) {
//
    for(int i = 0; i < size; i++){
        population_set[i] = Chromosome(size, fitnes_fun);
    }
}

template<typename n_type, typename f_type>
vector<double> Population<n_type, f_type>::calc_prob() {
//
    valarray<double> val_arr(population_set.size());
//
    for (int i = 0; i < population_set.size(); i++) {
        val_arr[i] = population_set[i].fitness;
    }
    double sum = val_arr.sum();
//
    valarray<double> perc_arr(val_arr.size());
//
    for (int j = 0; j < val_arr.size(); j++) {
        perc_arr[j] = val_arr[j]/sum;
    }
    perc_arr[0] += 1 - perc_arr.sum();
//
    vector<double> ended{perc_arr.size()};
//
    return ended;
}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::prob_crossover() {
//
    const vector<double> probabilities = calc_prob();
//
    vector<double> vec(calc_prob().size());
    srand (time(NULL) ); //initialize the random seed

    int RandIndex1 = rand() % population_set.size(); //generates a random number between 0 and
    Chromosome &chromosome1 = population_set[RandIndex1];
//
    int RandIndex2 = rand() % population_set.size(); //generates a random number between 0 and
    Chromosome & chromosome2 = population_set[RandIndex2];
//
    population_set[RandIndex1] = chromosome1.crossover(&chromosome2);
}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::prob_mutation() {
//
    for (Chromosome chromosome : population_set) {
//
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
//
        if(dis(gen)< prob_mut){
//            chromosome.mutate();
        }
    }
}

double wayToSort(Chromosome chromosome) { return chromosome.fitness;}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::refresh_nofit() {
    auto lethul_num = floor(size * lethal);

    valarray<Chromosome> to_sort_arr(population_set.size());
//
//    for (int i = 0; i < population_set.size(); i++) {
//        to_sort_arr[i] = population_set[i];
//    }
//
    sort(population_set.begin(), population_set.end(), wayToSort);
//
    Chromosome best = population_set[0];
    Chromosome worst = population_set[1];
//
    vector<Chromosome> sub_set = gen(lethul_num);

//    todo

}

template<typename n_type, typename f_type>
vector<Chromosome> Population<n_type, f_type>::gen(int leght) {
    vector<Chromosome> qweqfff(leght);
    for (int i = 0; i < leght; i++) {
        qweqfff[i] = Chromosome(leght, getFitnes_fun());
    }
    return qweqfff;
}
