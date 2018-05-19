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


    }

    int print_sth(Chromosome *other_chrom){
        return 0;
    }
    double GetLengthVector(){
        return 0;
    }
};

int main() {
    vector<int> x = {0,1,2,3,4};
    Chromosome lol = Chromosome(10,fit_func,x);
    Chromosome lal = Chromosome(5,fit_func,x);

//    vector<int> v;
//    for (int i= 0; i < 10; ++i) { v.push_back(i); }
//
//    slicer(v.begin(), v.begin() + v.size());

//    vector<int> v1 = {0,1,2,3};
//    vector<vector<int>> v2 = {{4,5},{6,7},{8,9}};
//    v_merge(v1,v2);
//    for(int i:v1){
//        cout<<i<<endl;
//    }
    return 0;
}