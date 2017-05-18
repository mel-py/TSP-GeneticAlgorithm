#ifndef ALGORITHM_H
#define ALFORITHM_H

#include "individual.h"
#include "population.h"
#include <vector>

class Algorithm {
public:
	Algorithm() {}
	Algorithm(std::vector<std::vector<int>> graph);

	Population evolvePopulation(Population pop);
	Individual crossover(Individual indiv1, Individual indiv2);
	Individual mutate(Individual inidv);
	std::vector<Individual> tournamentSelection(Population pop);

private:
	std::vector<std::vector<int>> _graph;
	int _geneLength;
	const double _UNIFORMRATE = 0.5;
	const double _MUTATIONRATE = 0.015;
};

#endif