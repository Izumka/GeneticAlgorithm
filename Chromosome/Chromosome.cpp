#include "Chromosome.h"
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
#include <sstream>
#include "functions.h"
#include "difflib.h"


using namespace std;

void Chromosome::Init(int len, std::vector<int> gene_vect) {
    this->length = len;
//    fitness_func = fit_fumc;
    if(gene_vect.size()){
        this->genes = gene_vect;
    }else{
        vector<int> x;

        for(int i = 0; i<(*this).length; i++){
            x.push_back(rand()%(*this).length);
        }

        this->genes = x;
    }
//    this->fitness = fitness_func((*this).genes);
}

vector<Chromosome> Chromosome::crossover(Chromosome *other_chrom) {
    map<string,Chromosome*> parents = {{"parent1",this}, {"parent2", other_chrom}};
//    cout<<(*this).length<<endl;
    vector<int> new_genes_1;
    vector<int> new_genes_2;

    int part_1 = rand() % ((*this).genes.size()) + 0;

    // Put part of parent one gene into new gene
    vector<vector<int>> container1 = {slicer((*parents["parent1"]).genes.begin(), (*parents["parent1"]).genes.begin() + part_1 + 1), slicer((*parents["parent2"]).genes.begin() + part_1, (*parents["parent2"]).genes.begin() + (*parents["parent1"]).genes.size())};
    v_merge(new_genes_1, container1);

    vector<vector<int>> container2 = {slicer((*parents["parent2"]).genes.begin(), (*parents["parent2"]).genes.begin() + part_1 + 1), slicer((*parents["parent1"]).genes.begin() + part_1, (*parents["parent1"]).genes.begin() + (*parents["parent2"]).genes.size())};
    v_merge(new_genes_2, container2);

    int new_length = (*this).length;
    function<int(vector<int>)> new_fitness_func = (*this).fitness_func;

    Chromosome child_1 = Chromosome(new_length, new_fitness_func, new_genes_1);
    Chromosome child_2 = Chromosome(new_length, new_fitness_func, new_genes_2);

    return vector<Chromosome>{child_1,child_2};
}
void Chromosome::mutate() {
    int swap_1 = rand() % ((*this).genes.size()) + 0;
    int swap_2 = rand() % ((*this).genes.size()) + 0;

    swap(this->genes[swap_1], this->genes[swap_2]);
}

void Chromosome::calc_fitnes() {
//    cout << "here2"<< endl;

    fitness = fitness_func(genes);

//    cout << "here3"<< endl;
}


void Chromosome::calc_ratio(Chromosome best_chromosome) {
    string a1 = vector_to_string((*this).genes);
    string a2 = vector_to_string(best_chromosome.genes);

    auto matcher = difflib::MakeSequenceMatcher(a1,a2);

    ratio = matcher.ratio();

}


std::string Chromosome::vector_to_string(std::vector<int> genes) {
    std::ostringstream oss;
    if (!genes.empty())
    {
        std::copy(genes.begin(), genes.end()-1,
                  std::ostream_iterator<int>(oss));

        oss << genes.back();
    }
    return oss.str();
}

Chromosome::Chromosome() {

}
