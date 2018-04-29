from Population import Population

if __name__ == "__main__":
    def fit(lst):
        n = len(lst)
        return sum([((i + 1) / n) * lst[i] for i in range(n)])
    population = Population(genes_length=5, num_type="int", fitness_fun=fit, size=10)

    population.generate_initial()
    print(population)

    population.refresh_nofit()
    print(population)

    while True:
        population.prob_crossover
        population.prob_mutation
        population.refresh_nofit()
        best = population.best_fit.fitness
        worst = population.worst_fit.fitness
        print(best, worst)
        if best/worst < 0.005:
            break
