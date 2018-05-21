#include "chromosome.h"
#include "population.h"
#include <string>
#include <vector>
#include <valarray>
#include <cmath>
#include <time.h>

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

//    const vector<double> samples{ 1, 2, 3, 4, 5, 6, 7 };
//    const vector<double> probabilities{ 0.1, 0.2, 0.1, 0.5, 0,1 };

    std::default_random_engine generator;
    std::discrete_distribution<int> distribution(probabilities.begin(), probabilities.end());

    vector<int> indices(vec.size());
    std::generate(indices.begin(), indices.end(), [&generator, &distribution]() { return distribution(generator); });

    std::transform(indices.begin(), indices.end(), vec.begin(), [&population_set](int index) { return population_set[index]; });
}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::prob_mutation() {

}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::refresh_nofit() {

}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::werwerwer() {

}
