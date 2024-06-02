#include "hybrid_evolution.hpp"

TSPSolution hybridEvolution(const TSPData& data, int populationSize, bool doLocalSearch, int stopTime) {
    std::vector<TSPSolution> population;
    while (population.size() < populationSize){
        TSPSolution solution = steepestEdges(data, generateRandomSolution(data));
        if(solution.distance > 0) {
            population.push_back(solution);
        }
        std::cout << "Initial solution distance: " << solution.distance << std::endl;
    }
    int numberOfGenerations = 0;
    int startTime = time(nullptr);
    std::cout << "Starting hybrid evolution" << std::endl;
    while (time(nullptr) - startTime < stopTime) {
        TSPSolution parent1 = population[rand() % populationSize];
        TSPSolution parent2;
        do {
          parent2 = population[rand() % populationSize];
        } while (parent2.distance == parent1.distance);
        TSPSolution child = cycleCrossover(data, parent1, parent2);
        if (doLocalSearch) {
            child = steepestEdges(data, child);
        }
        if (!isSolutionInPopulation(child, population)) {
            population.push_back(child);
        }
        std::sort(population.begin(), population.end(), compareSolutions);
        while(population.size() > populationSize){
            population.pop_back();
        }
        std::cout << "Best solution distance: " << population[0].distance << std::endl;
        numberOfGenerations++;
    }
    std::sort(population.begin(), population.end(), compareSolutions);
    population[0].numberOfIterations = numberOfGenerations;
    return population[0];
}

bool compareSolutions(const TSPSolution& a, const TSPSolution& b) {
    return a.distance < b.distance;
}

bool isSolutionInPopulation(const TSPSolution& solution, const std::vector<TSPSolution>& population) {
    for (const TSPSolution& s : population) {
        if (s.distance == solution.distance) {
            return true;
        }
    }
    return false;
}

TSPSolution cycleCrossover(const TSPData& data, const TSPSolution& parent1, const TSPSolution& parent2) {
    TSPSolution child = parent1;
    std::vector<int> toRemoveA;
    for (int i = 0; i < child.pathA.size(); i++) {
      if(edgeExistsAnywhere(parent2, child.pathA[i], child.pathA[(i + 1) % child.pathA.size()]).first == -1 && edgeExistsAnywhere(parent2, child.pathA[(i - 1 + child.pathA.size()) % child.pathA.size()], child.pathA[i]).first == -1){
        toRemoveA.push_back(child.pathA[i]);
      }
    }
    std::vector<int> toRemoveB;

    for (int i = 0; i < child.pathB.size(); i++) {
      if(edgeExistsAnywhere(parent2, child.pathB[i], child.pathB[(i + 1) % child.pathB.size()]).first == -1 && edgeExistsAnywhere(parent2, child.pathB[(i - 1 + child.pathB.size()) % child.pathB.size()], child.pathB[i]).first == -1) {
        toRemoveB.push_back(child.pathB[i]);
      }
    }
    for (int node : toRemoveA) {
      child.pathA.erase(std::remove(child.pathA.begin(), child.pathA.end(), node), child.pathA.end());
    }
    for (int node : toRemoveB) {
      child.pathB.erase(std::remove(child.pathB.begin(), child.pathB.end(), node), child.pathB.end());
    }
    return cycleAugmentation(data, child);
}