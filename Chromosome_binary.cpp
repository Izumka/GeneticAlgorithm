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


using namespace std;

//Vector slicer
typedef std::vector<int>::iterator vec_iter;

vector<int> slicer(vec_iter first, vec_iter last) {
    vector<int> fin;
    for (vec_iter cur = first; cur != last; ++cur) {
        cout<<*cur<<endl;
        fin.push_back(*cur);
    }
    return fin;
}

void v_merge(vector<int> &x1, const vector<vector<int>> &x2){
    for(int v=0; v<x2.size(); v++){
        for(int i=0; i<x2[v].size(); i++){
            x1.push_back(x2[v][i]);
        }
    }
}

// Fitness function
int fit_func(vector<int> x){
    return 0;
}

class Chromosome
{
public:
    int length;
    function<int(vector<int>)> fitness_func;
    vector<int> genes;
    double fitness;

    Chromosome(int len, function<int(vector<int>)> fitfunc ,vector<int> gene_vect=vector<int>{}){
        Init(len, fitfunc, gene_vect);
    }
    void Init(int len, function<int(vector<int>)> fitfunc, vector<int> gene_vect){
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
        this->fitness = fitness_func((*this).genes);
    }

    Chromosome crossover(Chromosome *other_chrom){
        map<string,Chromosome*> parents = {{"parent1",this}, {"parent2", other_chrom}};

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

        Chromosome child_1 = Chromosome(new_length, new_fitness_func, new_genes_1);
        Chromosome child_2 = Chromosome(new_length, new_fitness_func, new_genes_2);
        return(child_1,child_2);
    }

    void mutate(){
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

    int print_sth(Chromosome *other_chrom){
        return 0;
    }
};

//int main() {
//      vector<int> x = {1,1,0,0,1};
//      Chromosome lol = Chromosome(10,fit_func,x);
//      Chromosome lal = Chromosome(5,fit_func,x);
//      lol.mutate();
////      vector<int> v;
////      for (int i= 0; i < 12; ++i) { v.push_back(i); }
//////
////      slicer(v.begin(), v.begin() + (int)(v.size()/2));
////      cout<<"\n";
////      slicer(v.begin() + (int)(v.size()/2), v.begin() + v.size());
//
////      vector<int> v1 = {0,1,2,3};
////    vector<vector<int>> v2 = {{4,5},{6,7},{8,9}};
////    v_merge(v1,v2);
////    for(int i:v1){
////        cout<<i<<endl;
////    }
//    return 0;
//}