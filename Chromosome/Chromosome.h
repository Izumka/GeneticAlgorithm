
#ifndef CHROMOSOME_CHROMOSOME_H
#define CHROMOSOME_CHROMOSOME_H

#include <functional>
#include <iostream>
#include <vector>

class Chromosome {
private:
    int length;
    std::function<double (std::vector<int>)> fitness_func;
    std::vector<int> genes;

    void Init(int len, std::function<double (std::vector<int>)> fitfunc, std::vector<int> gene_vect);
public:
    double fitness;

    Chromosome(int len, std::function<double (std::vector<int>)> fitfunc ,std::vector<int> gene_vect=std::vector<int>{}){
        Init(len, fitfunc, gene_vect);
    }

    Chromosome crossover(Chromosome *other_chrom);

    void mutate();

    void calc_fitnes();

    int getLength() const {
        return length;
    }

    void setLength(int length) {
        Chromosome::length = length;
    }

    const std::function<double (std::vector<int>)> &getFitness_func() const {
        return fitness_func;
    }

    void setFitness_func(const std::function<double (std::vector<int>)> &fitness_func) {
        Chromosome::fitness_func = fitness_func;
    }

    const std::vector<int> &getGenes() const {
        return genes;
    }

    void setGenes(const std::vector<int> &genes) {
        Chromosome::genes = genes;
    }

    double getFitness() const {
        return fitness;
    }

    void setFitness(double fitness) {
        Chromosome::fitness = fitness;
    }
};

#endif //CHROMOSOME_CHROMOSOME_H
