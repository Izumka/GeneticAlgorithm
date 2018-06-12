#ifndef CHROMOSOME_POPULATION_H
#define CHROMOSOME_POPULATION_H

#include <iostream>
#include <functional>
#include <vector>
#include "../Chromosome/Chromosome.h"

//#pragma once



class Population {

private:
    int genes_length;
    int num_type;

    int size;
// Default config]

    double cross_prob;

    double prob_mut;
    double lethal;
    int theard_num;

//    Chromosome worst_fit;
// Additional data for logic

    std::vector<Chromosome> population_set;

    void calc_fithes();

    void calc_fit(int start, int end);

    void calculation_on_set();

    void calculation_on_set_ratio();

    void calc_ratio();
public:

    Chromosome best_fit;
//    double (*fitnes_fun)(std::vector<int>);

    std::function<double(std::vector<int>)> fitnes_fun;


    Population(int genes_length, int num_type, const std::function<double(std::vector<int>)> &fit_func, int size, int theard_num=1) : genes_length(genes_length),
                                                                                 num_type(num_type),
                                                                                  size(size), theard_num(theard_num),fitnes_fun(fit_func)
    {
//        std::cout << "Create population" << std::endl;
        ;
        cross_prob = 0.4;
        prob_mut = 0.05;
        lethal = 0.2;
        std::cout << "" << std::endl;
        this->generate_init();
        print_population();

    }

    void generate_init();

//    bool wayToSort(int i,int j);

    std::vector<Chromosome> generate_subset(int size);

    std::vector<double > calc_prob();

    void prob_crossover();

//    void prob_mutation();

    void refresh_nofit();

    std::vector<Chromosome> getPopulation_set() const {
        return population_set;
    }

    void setPopulation_set(std::vector<Chromosome> population_set) {
        Population::population_set = population_set;
    }


    double getCross_prob() const {
        return cross_prob;
    }



    double getProb_mut() const {
        return prob_mut;
    }

    double getLethal() const {
        return lethal;
    }

    int getGenes_length() const {
        return genes_length;
    }

    void setGenes_length(int genes_length) {
        Population::genes_length = genes_length;
    }

    int getNum_type() const {
        return num_type;
    }

    void setNum_type(int num_type) {
        Population::num_type = num_type;
    }


    int getSize() const {
        return size;
    }

    void setSize(int size) {
        Population::size = size;
    }

//    const std::function<double (std::vector<int>)> &getFitnes_fun() const {
//        return fitnes_fun;
//    }

    void print_population(){
        std::cout << "Population" << std::endl;
        for (Chromosome item : population_set) {
            for (auto set : item.getGenes()) {
                std::cout << set;
            }
            std::cout << ""<< std::endl;

        }
        std::cout << "\n" << std::endl;
    }


    virtual ~Population() {
        std::cout << "Chromosome is dead ;=)" << std::endl;
    }
};

#endif //LETS_DO_THAT_POPULATION_H


