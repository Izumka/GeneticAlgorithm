import random
import numpy as np

from Chromosome import Chromosome

class Population():

    def __init__(self, **kwargs):
        self.genes_length = kwargs["genes_length"]
        self.num_type = kwargs["num_type"]
        self.size = kwargs["size"]
        self.fitness_fun = kwargs["fitness_fun"]
        self.mutation_fun = kwargs["mutation_fun"]

    def generate_initial(self):
        self.population_set = []
        for _ in range(self.size):
            #genes = random.shuffle([ i for i in range(10) ])
            chromosome = Chromosome(num_type="int", length=self.genes_length,
                         fitness_fun=self.fitness_fun, mutation_fun=self.mutation_fun)
            chromosome.get_genes()
            self.population_set.append(chromosome)


if __name__ == "__main__":
    def always_fit():
        return 9

    def mutation_fun():
        return random.shuffle(self.genes)

    population = Population(genes_length=5, num_type="int", fitness_fun=always_fit, mutation_fun=mutation_fun, size=10)

    population.generate_initial()

    for chromosome in population.population_set:
        print(chromosome)
