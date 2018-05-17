import random

class Chromosome:
    def __init__(self, **kwargs):
        self.length = kwargs["length"]
        self.fitness_fun = kwargs["fitness_fun"]
        if "genes" in kwargs:
            self.genes = kwargs["genes"]
        else:
            self.genes = random.sample([i for i in range(0, self.length)], self.length)
        self.fitness = self.fitness_fun(self.genes)

    def __str__(self):
        return str(self.genes)

    def crossover(self, other):
        parents = {"parent_1": self, "parent_2": other}
        new_genes_1 = [-1] * self.length
        new_genes_2 = [-1] * self.length

        # Define who has better fitness & assign better fitness to parent 1
        if self.fitness < other.fitness:
            parents["parent_1"], parents["parent_2"] = parents["parent_2"], parents["parent_1"]

        # Generate random start and random length of gene copied
        mut_length = random.randint(int(self.length * 0.05), self.length - 1)
        mut_start = random.randint(0, self.length - mut_length - 1)

        # Put part of parent one gene into new gene
        new_genes_1 = new_genes_1[:mut_start] + parents["parent_1"].genes[mut_start: mut_start + mut_length] + new_genes_1[mut_start + mut_length:]
        new_genes_2 = new_genes_2[:mut_start] + parents["parent_2"].genes[mut_start: mut_start + mut_length] + new_genes_2[mut_start + mut_length:]

        for i in parents["parent_2"].genes:
            if i not in new_genes_1:
                new_genes_1[new_genes_1.index(-1)] = i

        for j in parents["parent_1"].genes:
            if j not in new_genes_2:
                new_genes_2[new_genes_2.index(-1)] = j

        length = self.length
        fitness_fun = self.fitness_fun

        child_1 = Chromosome(length=length, genes=new_genes_1, fitness_fun=fitness_fun)
        child_2 = Chromosome(length=length, genes=new_genes_2, fitness_fun=fitness_fun)
        return (child_1, child_2)

    def mutate(self):
        swap_1 = random.randint(0, self.length - 1)
        swap_2 = random.randint(0, self.length - 1)
        length = random.randint(int((self.length - swap_2) * 0.02), self.length - swap_2)
