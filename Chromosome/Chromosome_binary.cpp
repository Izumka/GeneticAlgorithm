#include "Chromosome_binary.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <cctype>
#include <map>
#include <functional>
#include <numeric>
#include <random>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <functional>
#include "functions.h"


using namespace std;

void Chromosome_binary::Init(int len, std::function<double (std::vector<int>)> fitfunc, std::vector<int> gene_vect) {
    this->length = len;
    this->fitness_func = fitfunc;
    if(gene_vect.size()){
        this->genes = gene_vect;
    }else{
        vector<int> x;

        srand ( time(NULL) );
        for(int i = 0; i<(*this).length; i++){
            x.push_back(rand()%(*this).length);
        }

        this->genes = x;
    }
//    this->fitness = fitness_func((*this).genes);
}

Chromosome_binary Chromosome_binary::crossover(Chromosome_binary *other_chrom) {
    map<string,Chromosome_binary*> parents = {{"parent1",this}, {"parent2", other_chrom}};

    vector<int> new_genes_1((*this).length);
    vector<int> new_genes_2((*this).length);

    int part_1 = rand() % ((*this).genes.size()) + 0;
    int part_2 = (*this).genes.size();

    // Put part of parent one gene into new gene
    vector<vector<int>> container1 = {slicer((*parents["parent1"]).genes.begin(), (*parents["parent1"]).genes.begin() + (int)((*parents["parent1"]).genes.size()/2) + 1), slicer((*parents["parent2"]).genes.begin() + (int)((*parents["parent1"]).genes.size()/2), (*parents["parent2"]).genes.begin() + (*parents["parent1"]).genes.size())};
    v_merge(new_genes_1, container1);

    vector<vector<int>> container2 = {slicer((*parents["parent2"]).genes.begin(), (*parents["parent2"]).genes.begin() + (int)((*parents["parent2"]).genes.size()/2) + 1), slicer((*parents["parent1"]).genes.begin() + (int)((*parents["parent2"]).genes.size()/2), (*parents["parent1"]).genes.begin() + (*parents["parent2"]).genes.size())};
    v_merge(new_genes_2, container2);

    int new_length = (*this).length;
    function<int(vector<int>)> new_fitness_func = (*this).fitness_func;

    Chromosome_binary child_1 = Chromosome_binary(new_length, new_fitness_func, new_genes_1);
    Chromosome_binary child_2 = Chromosome_binary(new_length, new_fitness_func, new_genes_2);
    return(child_1,child_2);
}

void Chromosome_binary::mutate() {
    srand ( time(NULL) );
    int swap_1 = rand() % ((*this).genes.size()) + 0;
    int swap_2 = rand() % ((*this).genes.size()) + 0;

    if((*this).genes[swap_1] == 1){
        this->genes[swap_1] = 0;
    }else{
        this->genes[swap_1] = 1;
    }

    if((*this).genes[swap_2] == 1){
        this->genes[swap_2] = 0;
    }else{
        this->genes[swap_2] = 1;
    }
}

void Chromosome_binary::calc_fitnes() {
        this->fitness = this->fitness_func((*this).genes);
}

