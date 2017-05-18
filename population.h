#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "individual.h"

class Population {
public:
	Population() {}
	Population(std::vector<std::vector<int>> graph, int popSize);

	Individual getIndividual(int index);
	Individual getFittest();
	int size();
	void saveIndividual(int index, Individual indiv);
	void addIndividual(Individual indiv);
	void removeIndividual(Individual indiv);

private:
	std::vector<Individual> _individuals;
};

#endif