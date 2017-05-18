#include "stdafx.h"
#include "individual.h"
#include <vector>
#include <random>
#include <time.h>
#include <iostream>

//create the individual by generating a hermitian graph and hope to god it's the solution
Individual::Individual(std::vector<std::vector<int>> graph, bool initalise) {

	this->_graph = graph;
	this->_geneLength = this->_graph.size();

	if (initalise) {
		for (int i = 0; i < graph.size(); i++) {
			int r = rand() % graph.size();
			//check if r is already in the vector, if it is choose another node
			while (std::find(this->_genes.begin(), this->_genes.end(), r) != this->_genes.end()) {
				r = rand() % this->_geneLength;
			}
			this->_genes.push_back(r);
		}
	}
	else {
		//set everything to null
		for (int i = 0; i < this->_geneLength; i++) {
			this->_genes.push_back(NULL);
		}
	}

	setFitness();
}

int Individual::getGene(int index) {
	return this->_genes.at(index);
}

int Individual::size() {
	return this->_geneLength;
}

void Individual::setGene(int index, int gene) {
	this->_genes.at(index) = gene;
	setFitness();
}

void Individual::addGene(int gene) {
	this->_genes.push_back(gene);
	setFitness();
}

//check if the gene already exists
//return -1 if not found
int Individual::findGene(int gene) {
	for (int i = 0; i < this->_geneLength; i++) {
		if (this->_genes.at(i) == gene) return i;
	}

	return -1;
}

void Individual::setFitness() {
	this->_fitness = 0;

	for (int i = 0; i < this->_geneLength; i++) {
		int j = i + 1;
		//account for the last link, the last item and the first in the vector counts as a link
		if (j >= this->_geneLength) {
			j = 0;
		}
		this->_fitness += this->_graph.at(this->_genes.at(i)).at(this->_genes.at(j));
	}
}

int Individual::getFitness() {
	return this->_fitness;
}

void Individual::printSolution() {
	for (int i = 0; i < this->_geneLength; i++) {
		std::cout << this->_genes.at(i) << " ";
	}

	std::cout << std::endl;
}

bool Individual::operator==(Individual& rhs) {
	bool equal = true;
	for (int i = 0; i < this->_geneLength; i++) {
		if (this->_genes.at(i) != rhs.getGene(i)) {
			equal = false;
		}
	}

	return equal;
}