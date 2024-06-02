#include "steepest.hpp"
#include "cycle_augmentation.hpp"

TSPSolution hybridEvolution(const TSPData& data, int populationSize, bool doLocalSearch, int stopTime);

bool isSolutionInPopulation(const TSPSolution& solution, const std::vector<TSPSolution>& population);

TSPSolution cycleCrossover(const TSPData& data, const TSPSolution& parent1, const TSPSolution& parent2);

bool compareSolutions(const TSPSolution& a, const TSPSolution& b);