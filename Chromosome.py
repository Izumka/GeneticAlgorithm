import random

class chromosome:
    def __init__(self, length, fitness_fun, num_type="bin", genes=[]):
        self.length = length
        self.genes = genes
        self.fitness = 0
        self.fitness_fun = fitness_fun
        self.num_type = num_type

    def get_fitness(self):
        if self.fitness < 0:
            self.fitness = self.fitness_fun(self.genes)
        return self.fitness

    def get_genes(self):
        if len(self.genes) == 0:
            self.genes = random.shuffle([i for i in range(0, 10)])
        return self.genes

    def __str__(self):
        return str([str(i) for i in self.genes])

    def crossover(self, other):
        parents = {"parent_1": self, "parent_2": other}

        # Define who has better fitness & assign better fitness to parent 1
        if self.fitness < other.fitness:
            parents["parent_1"], parents["parent_2"] = parents["parent_2"], parents["parent_1"]

        # Generate random start and random length of gene copied
        mut_length = random.randint(1, 8)
        mut_start = random.randint(0, self.length - mut_length - 1)
        new_genes = [0] * self.length

        # Put part of parent one gene into new gene
        new_genes = new_genes[:mut_start] + parents["parent_1"].genes[mut_start: mut_start + mut_length + 1] + new_genes[mut_start + mut_length:]
        #diff_genes = [i for i in ]
        for i in range(self.length):
            if new_genes[i] == 0 and parents["parent_2"].genes[i] not in new_genes:
                new_genes[i] = parents["parent_2"].genes[i]
            elif new_genes[i] == 0:
                pass
#                add_gene = [i for i in ]
        return

    def mutation(self):
        return