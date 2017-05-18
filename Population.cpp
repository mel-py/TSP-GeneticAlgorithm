#include "stdafx.h"
#include "population.h"

//create the population
Population::Population(std::vector<std::vector<int>> graph, int popSize) {
	for (int i = 0; i < popSize; i++) {
		Individual indiv(graph, true);
		this->_individuals.push_back(indiv);
	}
}

Individual Population::getIndividual(int index) {
	return this->_individuals.at(index);
}

//find the fittest individual in the population
//in this case smaller is better for simpler calculations
Individual Population::getFittest() {
	Individual fittest = this->_individuals.at(0);
	for (int i = 0; i < this->_individuals.size(); i++) {
		if (this->_individuals.at(i).getFitness() < fittest.getFitness()) {
			fittest = this->_individuals.at(i);
		}
	}

	return fittest;
}

int Population::size() {
	return this->_individuals.size();
}

void Population::saveIndividual(int index, Individual indiv) {
	this->_individuals.at(index) = indiv;
}

void Population::addIndividual(Individual indiv) {
	this->_individuals.push_back(indiv);
}

void Population::removeIndividual(Individual indiv) {
	for (int i = 0; i < size(); i++) {
		if (this->_individuals.at(i) == indiv) {
			this->_individuals.erase(this->_individuals.begin()+i);
		}
	}
}