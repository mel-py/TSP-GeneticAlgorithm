#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "stdafx.h"
#include <vector>

class Individual {
public:
	Individual() {}
	Individual(std::vector<std::vector<int>> graph, bool initalise);

	int getGene(int index);
	int size();
	void setGene(int index, int gene);
	void addGene(int gene);
	void setFitness();
	int findGene(int gene);
	int getFitness();

	void printSolution();
	
	bool operator==(Individual& rhs);

private:
	std::vector<std::vector<int>> _graph;
	int _geneLength;
	std::vector<int> _genes;
	int _fitness = 0;
};

#endif