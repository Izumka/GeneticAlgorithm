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



//void print_vector(std::vector<Chromosome> vector){
//    string string1 = "{";
//
//    for (Chromosome chromosome : vector ) {
//        string1 += chromosome.getFitness();
//}
//    string1 += "}";
//
//
//}



double fitnes_func(vector<int> lst){
    std::cout << "lets" << std::endl;

    int size = lst.size();

    valarray<double> arr_for_sum(size);

    for(int i = 0; i < size; i++){
        double num;
        num = ((i + 1)/ size) * lst[i];
        arr_for_sum[i] = num;
    }
    cout << arr_for_sum.sum() << endl;
    return arr_for_sum.sum();
}

class teat{
    int (*func_name)(vector<int>);
public:
    teat(int (*func_name)(vector<int>)) : func_name(func_name) {
        vector<int> shit = {1,1,2,3,2,54,4,1,87};
        func_name(shit);
    }
};

int main(){
    int b = 0;
    int * e = new int(1);
    cout << e << endl;
    cout << *e << endl;
    cout << &(*e) << endl;

    vector<int> shit = {1,1,2,3,2,54,4,1,87};
//    Population population = Population(10, 0, fitnes_func, 1);
//    population.generate_init();
////    population.fitnes_fun(shit);
//    Chromosome chromosome = Chromosome(10,fitnes_func, shit);
//    chromosome.calc_fitnes();

//    Population population = Population(5,0,fitnes_func, 1);
//    population.fitnes_fun(shit);

//    cout << population.fitnes_fun << endl;
//
//    population.generate_init();
//    cout << population.getPopulation_set()[0].fitness_func;


//    population.getPopulation_set()[0].calc_fitnes();




//    Chromosome chromosome = Chromosome(5, fitnes_func, {1,3,4,5,1,5});
//    chromosome.calc_fitnes();



//
    Population population = Population(5,0,fitnes_func,10);
    population.generate_init();
    cout << "sadads"<< endl;
//    print_vector(population.getPopulation_set());
    population.refresh_nofit();
//    print_vector(population.getPopulation_set());
    cout << ""<< endl;
    cout << "sldkf"<< endl;

    while(true){
        population.prob_crossover();
//        print_vector(population.getPopulation_set());
        population.prob_mutation();
//        print_vector(population.getPopulation_set());
        population.refresh_nofit();
//        print_vector(population.getPopulation_set());
        double best = population.getBest_fit();
        double worst = population.getWorst_fit();
        if(best/worst < 0.005){
            break;
        }
    }






    string string1 = "{";

//    for (int chromosome : shit) {
//        string1 += chromosome;
//    }
//    string1 += "}";











    return 0;
}
