#include "stdafx.h"
#include "algorithm.h"
#include <random>
#include <time.h>
#include <iostream>
#include <vector>

Algorithm::Algorithm(std::vector<std::vector<int>> graph) {
	this->_graph = graph;
}

Population Algorithm::evolvePopulation(Population pop) {
	Population newPop;

	newPop.addIndividual(pop.getFittest());

	for (int i = 1; i < pop.size(); i++) {
		std::vector<Individual> indivs = tournamentSelection(pop);
		Individual newIndiv = crossover(indivs.at(0), indivs.at(1));
		newPop.addIndividual(newIndiv);
	}

	for (int i = 1; i < newPop.size(); i++) {
		Individual mutation = mutate(newPop.getIndividual(i));
		newPop.saveIndividual(i, mutation);
	}

	return newPop;
}

Individual Algorithm::crossover(Individual indiv1, Individual indiv2) {
	Individual newSol(this->_graph, false);

	for (int i = 0; i < indiv1.size(); i++) {
		//crossover
		int r = rand() % 2;
		if (r <= this->_UNIFORMRATE) { //first individual
			/*check if the node already exists in new sol
			if not choose the first node that doesn't
			ensures the path remains connected and has no repeating nodes*/
			if (newSol.findGene(indiv1.getGene(i)) == -1) {
				newSol.setGene(i, indiv1.getGene(i));
			}
			else {
				//find the first node that isn't already in the new solution
				int j = 0;
				while (newSol.findGene(j) != -1 && j < (indiv1.size()-1)) {
					j++;
				}
				newSol.setGene(i, j);
			}
		}
		else { //repeat with second individual
			if (newSol.findGene(indiv2.getGene(i)) == -1) {
				newSol.setGene(i, indiv2.getGene(i));
			}
			else {
				//find the first node that isn't already in the new solution
				int j = 0;
				while (newSol.findGene(j) != -1 && j < (indiv1.size()-1)) {
					j++;
				}
				newSol.setGene(i, j);
			}
		}
	}

	return newSol;
}

Individual Algorithm::mutate(Individual indiv) {

	for (int i = 0; i < indiv.size(); i++) {
		if (rand() <= this->_MUTATIONRATE) {
			int randGene = rand() % indiv.size();
			//find the spot the generated node already exists in
			int j = indiv.findGene(randGene);

			//swap
			indiv.setGene(j, indiv.getGene(i));
			indiv.setGene(i, indiv.getGene(randGene));
		}
	}

	return indiv;
}

std::vector<Individual> Algorithm::tournamentSelection(Population pop) {
	Population tournament;
	std::vector<Individual> rouletteWheel;
	std::vector<Individual> fittest;

	int i = pop.size();
	while (pop.size() > 0){
		Individual fittest = pop.getFittest();
		pop.removeIndividual(fittest);
		for (int j = 0; j < i; j++) {
			rouletteWheel.push_back(fittest);
		}
		i--;
	}

	Individual indiv1, indiv2;
	int randId = rand() % rouletteWheel.size();
	indiv1 = rouletteWheel.at(randId);

	do {
		randId = rand() % rouletteWheel.size();
		indiv2 = rouletteWheel.at(randId);
	} while (indiv2 == indiv1);

	fittest.push_back(indiv1);
	fittest.push_back(indiv2);

	return fittest;
}