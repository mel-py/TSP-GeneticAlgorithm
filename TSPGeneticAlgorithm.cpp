// TSPGeneticAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "population.h"
#include <vector>
#include "algorithm.h"
#include <iostream>
#include <time.h>

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	std::vector<std::vector<int>> nodes;

	//set graph
	std::vector<int> node0 = { NULL, 2, 4, 3, 1, 2 };
	std::vector<int> node1 = { 2, NULL, 2, 3, 1, 4 };
	std::vector<int> node2 = { 4, 2, NULL, 3, 3, 2 };
	std::vector<int> node3 = { 3, 3, 3, NULL, 1, 2 };
	std::vector<int> node4 = { 1, 1, 3, 1, NULL, 2 };
	std::vector<int> node5 = { 2, 4, 2, 2, 2, NULL };

	nodes.push_back(node0);
	nodes.push_back(node1);
	nodes.push_back(node2);
	nodes.push_back(node3);
	nodes.push_back(node4);
	nodes.push_back(node5);

	Population pop(nodes, 5);
	Algorithm algorithm(nodes);

	/* generationCount is the total amount of generations gone through whereas generation
	   keeps track of the number of generations in which the fittest individual stays
	   the same */
	int generation = 0;
	int generationCount = 1;
	Individual fittest = pop.getFittest();

	while (generation <= 20) {
		std::cout << "Generation count: " << generationCount << std::endl;
		std::cout << "Fitness: " << fittest.getFitness() << std::endl;
		fittest.printSolution();

		//evolve the population
		Population newPop = algorithm.evolvePopulation(pop);
		generationCount++;

		Individual temp = newPop.getFittest();
		if (temp.getFitness() < fittest.getFitness()) {
			fittest = temp;
			generation = 0;
		}
		else {
			generation++;
		}

		pop = newPop;
	}

	std::cout << "Generation count: " << generationCount << std::endl;
	std::cout << "Solution found with fitness: " << fittest.getFitness() << std::endl;
	fittest.printSolution();

	system("PAUSE");

	return 0;
}