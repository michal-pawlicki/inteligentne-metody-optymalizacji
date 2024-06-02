#include "iterated_local_search.hpp"

TSPSolution iteratedLocalSearch(const TSPData& data, int stopTime) {
    int startTime = time(nullptr);
    TSPSolution bestSolution = steepestEdges(data, generateRandomSolution(data));
    TSPSolution currentSolution = bestSolution;
    int numberOfIterations = 0;
    while (time(nullptr) - startTime < stopTime) {
        TSPSolution perturbedSolution = perturb(data, currentSolution);
        TSPSolution localOptimum = steepestEdges(data, perturbedSolution);
        if (localOptimum.distance < currentSolution.distance) {
            currentSolution = localOptimum;
            if (currentSolution.distance < bestSolution.distance) {
                bestSolution = currentSolution;
            }
        }
        numberOfIterations++;
    }
    bestSolution.numberOfIterations = numberOfIterations;
    return bestSolution;
}

TSPSolution perturb(const TSPData& data, const TSPSolution& solution) {
    TSPSolution perturbedSolution = solution;
    for(int i = 0; i < 20; i++) {
        if(rand() % 2 == 0) {
            int pathIndex = rand() % 2;
            int i = rand() % solution.pathA.size();
            int j = rand() % solution.pathB.size();
            perturbedSolution = doInsideMoveEdges(solution, i, j, pathIndex);
        } else {
            int i = rand() % solution.pathA.size();
            int j = rand() % solution.pathB.size();
            perturbedSolution = doOutsideMove(solution, i, j);
        }
    }
    perturbedSolution.distance = calculateDistanceCycle(data, perturbedSolution.pathA) + calculateDistanceCycle(data, perturbedSolution.pathB);
    return perturbedSolution;
}