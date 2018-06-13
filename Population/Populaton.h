#ifndef CHROMOSOME_POPULATON_H
#define CHROMOSOME_POPULATON_H


#include <glob.h>
#include <iostream>
#include <vector>
#include <functional>
#include "../Chromosome/Chromosome.h"


class Populaton {
private:
    size_t chromosome_size;
    size_t population_size;

    double cross_prob;
    double prob_mut;
    double lethal;

    int theard_num;

    std::vector<Chromosome> population_set;

    Chromosome best_chromosome;

    void init();

    std::vector<Chromosome> generate_population(size_t population_size);

    void calculateProbability();


    void probabilry_crossover();
    void probabilry_mutate();
    void refresh_nofit();



public:

//    void parallel_calc_fitnes();
//    void parallel_calc_ratio();
//
//    void calc_fit(size_t start, size_t end);
//    void calc_ratio(size_t start, size_t end);

    std::function<double(std::vector<int>)> fitnes_func;

    Populaton(size_t chromosome_size, size_t population_size, const std::function<double(std::vector<int>)> &fitnes_fun, int theard_num=1) : chromosome_size(chromosome_size),
                                                                           population_size(population_size),
                                                                           theard_num(theard_num),
                                                                           fitnes_func(fitnes_fun) {
        cross_prob = 0.4;
        prob_mut = 0.05;
        lethal = 0.2;

        init();
        print_population();
    }

    void runAlgorithm();

    void print_population(){
        int iterator = 1;
        std::cout << "Population:" << std::endl;
        for (Chromosome item : population_set) {

            std::cout << iterator << " Genes(";
            for (auto set : item.getGenes()) {
                std::cout << set;

            }
            std::cout << ") ";
            std::cout << "Fitnes{"<< item.fitness << "} " ;
            std::cout << "Ratio{"<< item.ratio<< "}" ;
            std::cout << ""<< std::endl;
        iterator++;
        }
        std::cout << "" << std::endl;
    }

};


#endif //CHROMOSOME_POPULATON_H
