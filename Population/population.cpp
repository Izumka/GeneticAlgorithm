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

//using namespace std::vector;
using namespace std;

void Population::generate_init()
{

    cout << "1: Checking generate_init"<< endl;
    population_set = generate_subset(size);
    cout << "1: OK"<< endl;
}

vector<Chromosome> Population::generate_subset(int size)
{
    cout << "2: Checking generate_subset"<< endl;
    vector<Chromosome> population;
    cout << "2.1: Init chromosome vector"<< endl;


    for(int i = 0; i < size; i++)
    {
        population.push_back(Chromosome(genes_length, fitnes_fun));
    }
    cout << "2.2: Full the chromosome vector"<< endl;

    calc_fithes();
    cout << "2.3.: Calc the chromosome vector"<< endl;

    return population;
}

void Population::calc_fit(int start, int end)
{
    cout << "here"<< endl;
    cout << start<< endl;
    cout << end << endl;

    for (int i = start; i <= end; i++)
    {
        cout << i << endl;
        population_set[i].calc_fitnes();
        cout<< i << population_set[i].getFitness() << endl;
    }
}


void Population::calc_fithes()
{
    cout << "2.3.1: Checking cal_fitnes"<< endl;
    vector<thread> threads;
//
    int start = 0;
    int end = 0;


    cout << "2.3.2: Checking ..."<< endl;
    if(theard_num != 1){
        for (int i = 1; i <= theard_num; i++)
        {

            if(i == theard_num)
            {
                cout << "num of thread = "<< i<< endl;
                end = size;
            }
            else
            {
            end += size/theard_num ;
            }
            threads.push_back(thread(&Population::calc_fit,this, start, end));
            start = end;
            cout << "Add thread"<< endl;
        }
        cout << "Checking...2"<< endl;
        for (int i = 0; i < theard_num; i++)
        {
            cout << "Checking join"<< endl;
            threads[i].join();
            cout << "Checking join"<< endl;
        }
    }
    else
    {
        cout << "1 thread"<< endl;
        for (int i = 0; i < size; i++)
        {
            cout << i << endl;
            population_set[i].calc_fitnes();
        }
    }
}

vector<double> Population::calc_prob()
{
    std::valarray<double> val_arr(population_set.size());
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
    vector<double> ended(perc_arr.size());
//
    return ended;
}

void Population::prob_crossover()
{
//    const vector<double> probabilities = calc_prob();
//
//    vector<double> vec(calc_prob().size());
//
//    const vector<double> samples{ 1, 2, 3, 4, 5, 6, 7 };
//    const vector<double> probabilities{ 0.1, 0.2, 0.1, 0.5, 0,1 };
//
//    std::default_random_engine generator;
//    std::discrete_distribution<int> distribution(probabilities.begin(), probabilities.end());
//
//    vector<int> indices(vec.size());
//    generate(indices.begin(), indices.end(), [&generator, &distribution]() { cout<< distribution(generator); });

//    transform(indices.begin(), indices.end(), vec.begin(), [population_set](int index) { population_set[index].});
}


void Population::prob_mutation()
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

//bool Population::wayToSort(int i,int j)
//{
//    return (population_set[i].getFitness()<population_set[j].getFitness());
//}

void Population::refresh_nofit()
{

    auto lethul_num = static_cast<int>(floor(size * lethal));

    double fitnes_array[population_set.size()];

    for (int k = 0; k < population_set.size() ; k++)
    {
        fitnes_array[k] = population_set[k].getFitness();
    }
    sort(fitnes_array, fitnes_array + population_set.size());
    //

    vector<Chromosome> new_population;

    for (int l = 0; l < size; l++)
    {
        for (int p = 0; l < size; p++)
        {
            if(fitnes_array[l] == population_set[p].getFitness())
            {
                new_population[l] = population_set[p];
                population_set.erase(population_set.begin()+p);
            }
        }
    }

    population_set = new_population;

    Chromosome best = population_set[size - 1];
    Chromosome worst = population_set[size - 2];
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

