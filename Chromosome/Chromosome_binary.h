//
// Created by oles on 24.05.18.
//

#ifndef CHROMOSOME_CHROMOSOME_BINARY_H
#define CHROMOSOME_CHROMOSOME_BINARY_H

#include <functional>
#include <iostream>
#include <vector>

class Chromosome_binary {
private:
    int length;
    std::function<double (std::vector<int>)> fitness_func;
    std::vector<int> genes;

    void Init(int len, std::function<double (std::vector<int>)> fitfunc, std::vector<int> gene_vect);
public:
    double fitness;

    Chromosome_binary(int len, std::function<double (std::vector<int>)> fitfunc ,std::vector<int> gene_vect=std::vector<int>{}){
        Init(len, fitfunc, gene_vect);
    }

    Chromosome_binary crossover(Chromosome_binary *other_chrom);

    void mutate();

    void calc_fitnes();

    int getLength() const {
        return length;
    }

    const std::function<double (std::vector<int>)> &getFitness_func() const {
        return fitness_func;
    }

    const std::vector<int> &getGenes() const {
        return genes;
    }

    double getFitness() const {
        return fitness;
    }

};


#endif //CHROMOSOME_CHROMOSOME_BINARY_H
