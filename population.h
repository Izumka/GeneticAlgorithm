#ifndef CHROMOSOME_POPULATION_H
#define CHROMOSOME_POPULATION_H

#include <iostream>
//#pragma once

template <typename n_type, typename f_type>


class Population {

private:
    int genes_length;
    n_type num_type;
    function<f_type(vector<f_type>)> fitnes_fun ;
    int size;

// Default config]

    double cross_prob;
    double prob_mut;
    double lethal;

// Additional data for logic

    std::vector<Chromosome> population_set{size};


public:

    Population(int genes_length, n_type num_type, function<f_type(vector<f_type>)> fitnes_fun, int size) : genes_length(genes_length),
                                                                                 num_type(num_type),
                                                                                 fitnes_fun(fitnes_fun), size(size) {
        cross_prob = 0.4;
        prob_mut = 0.05;
        lethal = 0.2;
    }

    void generate_subset(int size);

    std::vector<double > calc_prob();

    void prob_crossover();

    void prob_mutation();

    void refresh_nofit();



    vector<Chromosome> gen(int leght);

    vector<Chromosome> getPopulation_set() const {
        return population_set;
    }

    void setPopulation_set(vector<Chromosome> population_set) {
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

    n_type getNum_type() const {
        return num_type;
    }

    void setNum_type(n_type num_type) {
        Population::num_type = num_type;
    }


    int getSize() const {
        return size;
    }

    void setSize(int size) {
        Population::size = size;
    }

    const function<f_type(vector<f_type>)> &getFitnes_fun() const {
        return fitnes_fun;
    }

    virtual ~Population() {
        std::cout << "Chromosome is dead ;=)" << endl;
    }
};


#endif //LETS_DO_THAT_POPULATION_H


