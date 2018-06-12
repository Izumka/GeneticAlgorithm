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

//    cout << "1: Checking generate_init"<< endl;
    population_set = generate_subset(genes_length);
    calculation_on_set();
//    cout << "1: OK"<< endl;
}

vector<Chromosome> Population::generate_subset(int size){
//    cout << "2: Checking generate_subset"<< endl;
    vector<Chromosome> population;
//    cout << "2.1: Init chromosome vector"<< endl;



    for(int i = 0; i < size; i++)
    {
        population.push_back(Chromosome(this->size, fitnes_fun));
    }
//    cout << "2.2: Full the chromosome vector"<< endl;
    return population;
}


void Population::calculation_on_set()
{
    calc_fithes();
//    cout << "2.3.: Calc the chromosome vector"<< endl;
}

void Population::calc_fit(int start, int end)
{
//    cout << "here"<< endl;
//    cout << start<< endl;
//    cout << end << endl;

    for (int i = start; i <= end; i++)
    {
//        cout << i << end;
        population_set[i].calc_fitnes();
//        cout<< i << population_set[i].getFitness() << endl;
    }
}


void Population::calc_fithes()
{
//    cout << "2.3.1: Checking cal_fitnes"<< endl;
    vector<thread> threads;
//
    int start = 0;
    int end = 0;


//    cout << "2.3.2: Checking ..."<< endl;
    if(theard_num != 1){
        for (int i = 1; i <= theard_num; i++)
        {

            if(i == theard_num)
            {
//                cout << "num of thread = "<< i<< endl;
                end = size;
            }
            else
            {
            end += size/theard_num ;
            }
            threads.push_back(thread(&Population::calc_fit,this, start, end));
            start = end;
//            cout << "Add thread"<< endl;
        }
//        cout << "Checking...2"<< endl;
        for (int i = 0; i < theard_num; i++)
        {
//            cout << "Checking join"<< endl;
            threads[i].join();
//            cout << "Checking join"<< endl;
        }
    }
    else
    {
//        cout << "1 thread"<< endl;
        for (int i = 0; i < population_set.size(); i++)
        {
//            cout << i << endl;
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
//
    for (int j = 0; j < val_arr.size(); j++)
    {
        perc_arr[j] = ((val_arr[j]/sum)* (1 - retio_arr[j]));
    }
    perc_arr[0] += 1 - perc_arr.sum();
//
    vector<double> ended;
    for (auto  item: perc_arr ) {
        ended.push_back(item);
    }
//
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

    // prefix[n-1] is sum of all frequencies. Generate a random number
    // with value from 1 to this sum
    int r = (rand() % prefix.at(n - 1)) + 1;

    // Find index of ceiling of r in prefix arrat
    int indexc = findCeilVec(prefix, r, 0, n - 1);
    return arr.at(indexc);

}

void Population::prob_crossover()
{
    const vector<double> probabilities = calc_prob();
    for (auto  item: probabilities ) {
        cout << item << " ";
}
    cout << "" << endl;

    vector<int> index_vec = {0,1,2,3,4,5,6,7,8,9} ;



    for (auto  item: population_set) {
        bool same;

        int chomosome_index = myRandVec(index_vec, probabilities, population_set.size());
        int other_index = myRandVec(index_vec, probabilities, population_set.size());
        Chromosome chromosome = population_set[chomosome_index];
        Chromosome other = population_set[other_index];


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

        if (other_index == chomosome_index){
            population_set.erase(population_set.begin() + chomosome_index  - 1);
            chromosome.crossover(&other);
            population_set.push_back(chromosome);
        } else{
            population_set.erase(population_set.begin() + chomosome_index - 1);
            chromosome.crossover(&other);
            population_set.insert(population_set.begin() + chomosome_index - 1, chromosome);
            population_set.erase(population_set.begin() + other_index - 1);
            other.crossover(&chromosome);
            population_set.push_back(other);
        }



}



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

