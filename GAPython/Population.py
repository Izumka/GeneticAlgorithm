import random
import numpy as np

from math import floor

from Chromosome import Chromosome

class Population():

    def __init__(self, **kwargs):
        self.genes_length = kwargs["genes_length"]
        self.num_type = kwargs["num_type"]
        self.size = kwargs["size"]
        self.fitness_fun = kwargs["fitness_fun"]
        #default configuration
        self.cross_prob = 0.4
        self.prob_mut = 0.05
        self.lethal = 0.2

    def generate_initial(self):
        self.population_set = self.generate_subset(self.size)

    def generate_subset(self, chrom_num):
        tmp_arr = []
        for _ in range(chrom_num):
            chromosome = Chromosome(num_type="int", length=self.genes_length,
                         fitness_fun=self.fitness_fun)
            chromosome.get_genes()
            tmp_arr.append(chromosome)
        return tmp_arr

    def calc_prob(self):
        #generate weighted array of probability for each chromosome, based on fitness
        val_arr = [ i.fitness for i in self.population_set ]
        fitn_sum = np.sum(val_arr)
        perc_arr = [ round(i/fitn_sum, 2) for i in val_arr ]
        perc_arr[0] += 1 - np.sum(perc_arr)
        return perc_arr

    def prob_crossover(self):
        #weightened pop 2 chromosomes from set, crossover them, append back to set
        weights = self.calc_prob()
        for _ in range(floor(self.size*self.cross_prob)):
            chrom = np.random.choice(self.population_set, p=weights)
            other_chrom = np.random.choice(self.population_set, p=weights)
            population_set.remove(chrom)
            population_set.remove(other_chrom)
            chrom, other_chrom = chrom.crossover(other_chrom)
            population_set.append(chrom)
            population_set.append(other_chrom)

    def prob_mutation(self):
        #mutate every chromosome
        for chrom in self.population_set:
            if random.random() < self.prob_mut:
                chrom.mutate()

    def refresh_nofit(self): #kill lower part of less fit individuals, append lack of them
        lethal_num = floor(self.size*self.lethal)
        self.population_set.sort(key=lambda x: x.fitness, reverse=True)
        sub_set = self.generate_subset(lethal_num)
        self.population_set = self.population_set[:(self.size-lethal_num)]
        self.population_set.extend(sub_set)

    def __str__(self):
        return " ".join([str(i) for i in self.population_set])

if __name__ == "__main__":
    def always_fit():
        return "YEAA"
    population = Population(genes_length=5, num_type="int", fitness_fun=always_fit, size=10)

    population.generate_initial()
    print(population)

    population.refresh_nofit()
    print(population)
