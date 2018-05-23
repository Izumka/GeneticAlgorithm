#include "chromosome.h"
#include "population.h"
#include <string>
#include <vector>
#include <valarray>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <thread>

using namespace std;


template<typename n_type, typename f_type>
void Population<n_type, f_type>::generate_init()
{
    population_set = generate_subset(size);
}

template<typename n_type, typename f_type>
vector<Chromosome> Population<n_type, f_type>::generate_subset(int size)
{
    vector<Chromosome> population;

    for(int i = 0; i < size; i++)
    {
        population.push_back(Chromosome(genes_length, fitnes_fun));
    }
    calc_fithes();

    return population;
}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::calc_fit(int start, int end)
{
    for (int i = start; i < end; i++)
    {
        population_set[i].get_fitness();
    }
}


template<typename n_type, typename f_type>
void Population<n_type, f_type>::calc_fithes()
{
    vector<thread> threads;
//
    int start = 0;
    int end = 0;
//
    for (int i = 1; i <= theard_num; i++)
    {
        if(i == theard_num)
        {
            end = population_set.size();
        }
        else
        {
        end += size/theard_num ;
        }
        threads.push_back(thread(calc_fit, start, end));
        start = end;
    }
    for (int i = 0; i < 4; i++)
    {
        threads[i].join();
    }
}

template<typename n_type, typename f_type>
vector<double> Population<n_type, f_type>::calc_prob()
{
    valarray<double> val_arr(population_set.size());
//
    for (int i = 0; i < population_set.size(); i++)
    {
        val_arr[i] = population_set[i].fitness;
    }

    double sum = val_arr.sum();
    valarray<double> perc_arr(val_arr.size());
//
    for (int j = 0; j < val_arr.size(); j++)
    {
        perc_arr[j] = val_arr[j]/sum;
    }
    perc_arr[0] += 1 - perc_arr.sum();
//
    vector<double> ended{perc_arr.size()};
//
    return ended;
}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::prob_crossover()
{
    const vector<double> probabilities = calc_prob();

    vector<double> vec(calc_prob().size());

//    const vector<double> samples{ 1, 2, 3, 4, 5, 6, 7 };
//    const vector<double> probabilities{ 0.1, 0.2, 0.1, 0.5, 0,1 };

    std::default_random_engine generator;
    std::discrete_distribution<int> distribution(probabilities.begin(), probabilities.end());

    vector<int> indices(vec.size());
    generate(indices.begin(), indices.end(), [&generator, &distribution]() { cout<< distribution(generator); });

//    transform(indices.begin(), indices.end(), vec.begin(), [population_set](int index) { population_set[index].});
}


template<typename n_type, typename f_type>
void Population<n_type, f_type>::prob_mutation()
{
    for (Chromosome chromosome : population_set)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(0, 1);
//
        if(dis(gen)< prob_mut)
        {
            chromosome.mutate();
        }
    }
}

double wayToSort(Chromosome chromosome) { return chromosome.fitness;}

template<typename n_type, typename f_type>
void Population<n_type, f_type>::refresh_nofit()
{
    auto lethul_num = floor(size * lethal);
//
    valarray<Chromosome> to_sort_arr(population_set.size());
//
    sort(population_set.begin(), population_set.end(), wayToSort);
//
    Chromosome best = population_set[0];
    Chromosome worst = population_set[1];
//
    vector<Chromosome> sub_set = generate_subset(lethul_num);
    vector<Chromosome> one;
//

    for (int i = 0; i < population_set.size() - lethul_num ; i++)
    {
        one[i] = population_set[i];
    }
    for (int j = (population_set.size() - lethul_num), b =0; j < population_set.size() ; j++, b++)
    {
        one[j] = sub_set[b];
    }
    population_set = one;
}

