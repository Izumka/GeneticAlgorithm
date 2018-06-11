#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <valarray>
#include <thread>
#include "Chromosome/Chromosome.h"
#include "Population/population.h"

using std::vector;
using namespace std;


double fitnes_func(vector<int> lst){
//    std::cout << "lets" << std::endl;

    int size = lst.size();

    valarray<double> arr_for_sum(size);

    for(int i = 0; i < size; i++){
        double num;
        num = ((i + 1)/ size) * lst[i];
        arr_for_sum[i] = num;
    }
//    cout << arr_for_sum.sum() << endl;
    return arr_for_sum.sum();
}

int main(){
    int b = 0;
    int * e = new int(1);
    cout << e << endl;
    cout << *e << endl;
    cout << &(*e) << endl;

    vector<int> shit = {1,1,2,3,2,54,4,1,87};
    Population population = Population(5,0,fitnes_func,1);
    population.generate_init();
//    cout << "sadads"<< endl;
//    population.refresh_nofit();
//    cout << ""<< endl;
//    cout << "sldkf"<< endl;

    while(true){
//        population.prob_crossover();
        population.prob_mutation();
//        population.refresh_nofit();
        double best = population.getBest_fit();
        double worst = population.getWorst_fit();
        if(best/worst < 0.005){
            break;
        }
    }
    string string1 = "{";











    return 0;
}
