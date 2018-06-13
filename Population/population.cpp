#include "../Chromosome/Chromosome.h"
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


bool fit_sort (Chromosome i,Chromosome j) { return (i.fitness>j.fitness); }

void Population::generate_init()
{

    population_set = generate_subset(population_size);
    calculation_on_set();
    sort(population_set.begin(), population_set.end(), fit_sort);
    best_fit = population_set[0];
    calculation_on_set_ratio();
}

vector<Chromosome> Population::generate_subset(size_t population_size){

    vector<Chromosome> population;
        srand ( time(NULL) );
    for(int i = 0; i < population_size; i++)
    {
        population.push_back(Chromosome(this->chromosome_size, fitnes_fun));
    }

    return population;
}

void Population::calculation_on_set()
{
    calc_fithes();
}

void Population::calculation_on_set_ratio()
{
    calc_ratio();
}

void Population::calc_fit(int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        population_set[i].calc_fitnes();
    }
}

void Population::calc_ratio() {


    vector<thread> threads;
    int start = 0;
    int end = 0;

    if(theard_num != 1){
        for (int i = 1; i <= theard_num; i++)
        {
            if(i == theard_num)
            {
                end = population_size;
            }
            else
            {
                end += population_size/theard_num ;
            }
            threads.push_back(thread(&Population::calc_fit,this, start, end));
            start = end;
        }
        for (int i = 0; i < theard_num; i++)
        {
            threads[i].join();
        }
    }
    else
    {
        for (int i = 0; i < population_set.size(); i++)
        {
            population_set[i].calc_ratio(best_fit);
        }
    }
}


void Population::calc_fithes()
{
    vector<thread> threads;
    int start = 0;
    int end = 0;

    if(theard_num != 1){
        for (int i = 1; i <= theard_num; i++)
        {
            if(i == theard_num)
            {
                end = population_size;
            }
            else
            {
            end += population_size/theard_num ;
            }
            threads.push_back(thread(&Population::calc_fit,this, start, end));
            start = end;
        }
        for (int i = 0; i < theard_num; i++)
        {
            threads[i].join();
        }
    }
    else
    {
        for (int i = 0; i < population_set.size(); i++)
        {
            population_set[i].calc_fitnes();
        }
    }
}

vector<double> Population::calc_prob()
{
    std::valarray<double> val_arr(population_set.size());
    vector<double> retio_arr(population_set.size());

    for (int i = 0; i < population_set.size(); i++)
    {
        val_arr[i] = population_set[i].fitness;
        retio_arr[i] = population_set[i].ratio;
    }

    double sum = val_arr.sum();
    valarray<double> perc_arr(val_arr.size());
    for (int j = 0; j < val_arr.size(); j++)
    {
        perc_arr[j] = ((val_arr[j]/sum)* (1 - retio_arr[j]));
    }
    perc_arr[0] += 1 - perc_arr.sum();
    vector<double> ended;
    for (auto  item: perc_arr ) {
        ended.push_back(item);
    }
    return ended;
}

int findCeilVec(vector<int> arr, int r, int l, int h){
    int mid;
    while (l < h)
    {
        mid = l + ((h - l) >> 1);  // Same as mid = (l+h)/2
        (r > arr.at(mid)) ? (l = mid + 1) : (h = mid);
    }
    return (arr.at(l) >= r) ? l : -1;
}

int myRandVec(vector<int> arr, vector<double> freq, int n){
    vector<int> prefix;
    int j;

    prefix.push_back(arr.at(0));

    for (j = 1; j < n; ++j)
        prefix.push_back(prefix.at(j - 1) + arr.at(j));

    int r = (rand() % prefix.at(n - 1)) + 1;

    int indexc = findCeilVec(prefix, r, 0, n - 1);
    return arr.at(indexc);

}

void Population::prob_crossover()
{


    vector<int> index_vec = {0,1,2,3,4,5,6,7,8,9} ;



    for (auto  item: population_set) {
        const vector<double> probabilities = calc_prob();
        for (auto  item: probabilities ) {
            cout << item << " ";
        }
        cout << "" << endl;
        bool same;

        int chomosome_index = myRandVec(index_vec, probabilities, population_set.size());
        int other_index = myRandVec(index_vec, probabilities, population_set.size());
        Chromosome chromosome = population_set[chomosome_index];
        Chromosome other = population_set[other_index];

        std::cout << "1> " << chomosome_index << std::endl;
        std::cout << "2> " << other_index << std::endl;

        cout<< "Chromosome 1: ";
        for (int i : chromosome.getGenes()) {
            cout << i << " ";
        }
        cout << ""<< endl;

        cout<< "Chromosome 2: ";
        for (int i : other.getGenes()) {
            cout << i << " ";
        }
        cout << ""<< endl;

        srand ( time(NULL) );
        if (other_index == chomosome_index){
            population_set.erase(population_set.begin() + chomosome_index);
            chromosome.crossover(&other);
            population_set.push_back(chromosome);
        } else{
            population_set.erase(population_set.begin() + chomosome_index);
            chromosome.crossover(&other);
            population_set.insert(population_set.begin() + chomosome_index, chromosome);
            population_set.erase(population_set.begin() + other_index );
            other.crossover(&chromosome);
            population_set.push_back(other);
        }
        calc_fithes();
    }
}



void Population::refresh_nofit()
{

    auto lethul_num = static_cast<int>(floor(population_size * lethal));

    double fitnes_array[population_set.size()];

    for (int k = 0; k < population_set.size() ; k++)
    {
        fitnes_array[k] = population_set[k].getFitness();
    }
    sort(fitnes_array, fitnes_array + population_set.size());
    //

    vector<Chromosome> new_population;

    for (int l = 0; l < chromosome_size; l++)
    {
        for (int p = 0; l < chromosome_size; p++)
        {
            if(fitnes_array[l] == population_set[p].getFitness())
            {
                new_population[l] = population_set[p];
                population_set.erase(population_set.begin()+p);
            }
        }
    }

    population_set = new_population;

    Chromosome best = population_set[population_size - 1];
    Chromosome worst = population_set[population_size - 2];
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

