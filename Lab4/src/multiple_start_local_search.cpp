#include "multiple_start_local_search.hpp"

TSPSolution multipleStartLocalSearch(const TSPData& data, int iterations) {
    TSPSolution bestSolution;
    bestSolution.distance = std::numeric_limits<double>::infinity();

    for (int i = 0; i < iterations; i++) {
        TSPSolution solution = steepestEdges(data, generateRandomSolution(data));
        if (solution.distance < bestSolution.distance) {
            bestSolution = solution;
        }
        std::cout << "Iteration " << i << ": " << bestSolution.distance << std::endl;
    }

    return bestSolution;
}