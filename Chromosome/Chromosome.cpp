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

Chromosome Chromosome::crossover(Chromosome *other_chrom) {
    map<string,Chromosome*> parents = {{"parent1",this}, {"parent2", other_chrom}};

    vector<int> new_genes_1((*this).length);
    vector<int> new_genes_2((*this).length);
    fill(new_genes_1.begin(),new_genes_1.begin()+(*this).length,-1);
    fill(new_genes_2.begin(),new_genes_2.begin()+(*this).length,-1);

    // Define who has better fitness & assign better fitness to parent 1
    if((*this).fitness < (*other_chrom).fitness){
        parents["parent1"] = other_chrom;
        parents["parent2"] = this;
    }

    // Generate random start and random length of gene copied
    srand ( time(NULL) );
    int mut_length = (int)(rand() % ((*this).length - 1) + (*this).length * 0.05);
    int mut_start = rand() % ((*this).length - mut_length - 1) + 0;

    // Put part of parent one gene into new gene
    vector<vector<int>> container1 = {slicer(new_genes_1.begin(), new_genes_1.begin() + mut_start + 1), slicer((*parents["parent1"]).genes.begin() + mut_start, (*parents["parent1"]).genes.begin() + mut_start + mut_length), slicer(new_genes_1.begin() + mut_start + mut_length, new_genes_1.begin() + new_genes_1.size())};
    v_merge(new_genes_1, container1);

    vector<vector<int>> container2 = {slicer(new_genes_2.begin(), new_genes_2.begin() + mut_start + 1), slicer((*parents["parent2"]).genes.begin() + mut_start, (*parents["parent2"]).genes.begin() + mut_start + mut_length), slicer(new_genes_2.begin() + mut_start + mut_length, new_genes_2.begin() + new_genes_2.size())};
    v_merge(new_genes_2, container2);

    for(int i: (*parents["parent2"]).genes){
        if(find(new_genes_1.begin(), new_genes_1.end(), i) == new_genes_1.end()){
            int pos = find(new_genes_1.begin(), new_genes_1.end(), -1) - new_genes_1.begin();
            if(!pos>=new_genes_1.size()){
                new_genes_1[pos] = i;
            }
        }
    }

    for(int j: (*parents["parent1"]).genes){
        if(find(new_genes_2.begin(), new_genes_2.end(), j) == new_genes_2.end()){
            int pos = find(new_genes_2.begin(), new_genes_2.end(), -1) - new_genes_2.begin();
            if(!pos>=new_genes_2.size()){
                new_genes_2[pos] = j;
            }
        }
    }

    int new_length = (*this).length;
//    double (*new_fit_fumc)(std::vector<int>)();
//    new_fit_fumc = fitness_func;

    Chromosome child_1 = Chromosome(new_length, fitness_func, new_genes_1);
    Chromosome child_2 = Chromosome(new_length, fitness_func, new_genes_2);
    return(child_1,child_2);
}

void Chromosome::mutate() {
    srand ( time(NULL) );
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
