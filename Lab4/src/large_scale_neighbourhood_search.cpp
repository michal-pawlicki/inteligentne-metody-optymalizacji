#include "large_scale_neighbourhood_search.hpp"

TSPSolution largeScaleNeighbourhoodSearch(const TSPData& data, bool doLocalSearch, int stopTime) {
    TSPSolution bestSolution = steepestEdges(data, generateRandomSolution(data));
    TSPSolution currentSolution = bestSolution;
    int startTime = time(nullptr);
    int numberOfIterations = 0;
    while (time(nullptr) - startTime < stopTime) {
        TSPSolution destroyedSolution = destroy(currentSolution);
        TSPSolution repairedSolution = repair(data, destroyedSolution);
        if(doLocalSearch) {
            repairedSolution = steepestEdges(data, repairedSolution);
        }
        if (repairedSolution.distance < currentSolution.distance) {
            currentSolution = repairedSolution;
            if (currentSolution.distance < bestSolution.distance) {
                bestSolution = currentSolution;
            }
        }
        numberOfIterations++;
    }
    bestSolution.numberOfIterations = numberOfIterations;
    return bestSolution;
}

TSPSolution destroy(const TSPSolution& solution) {
    TSPSolution destroyedSolution = solution;
    int n = solution.pathA.size();
    int k = (n * 0.30 )/ 2;
    int randomIndex1 = rand() % n;
    int randomIndex2 = randomIndex1 + k;
    if (randomIndex2 < n) {
        destroyedSolution.pathA.erase(destroyedSolution.pathA.begin() + randomIndex1, destroyedSolution.pathA.begin() + randomIndex2);
    } else {
        destroyedSolution.pathA.erase(destroyedSolution.pathA.begin() + randomIndex1, destroyedSolution.pathA.end());
        destroyedSolution.pathA.erase(destroyedSolution.pathA.begin(), destroyedSolution.pathA.begin() + randomIndex2 - n);
    }
    n = solution.pathB.size();
    randomIndex1 = rand() % n;
    randomIndex2 = randomIndex1 + k;
    if (randomIndex2 < n) {
        destroyedSolution.pathB.erase(destroyedSolution.pathB.begin() + randomIndex1, destroyedSolution.pathB.begin() + randomIndex2);
    } else {
        destroyedSolution.pathB.erase(destroyedSolution.pathB.begin() + randomIndex1, destroyedSolution.pathB.end());
        destroyedSolution.pathB.erase(destroyedSolution.pathB.begin(), destroyedSolution.pathB.begin() + randomIndex2 - n);
    }
    TSPSolution destroyedSolution2 = destroyedSolution;
    n = destroyedSolution.pathA.size();
    randomIndex1 = rand() % n;
    randomIndex2 = randomIndex1 + k;
    if (randomIndex2 < n) {
        destroyedSolution2.pathA.erase(destroyedSolution2.pathA.begin() + randomIndex1, destroyedSolution2.pathA.begin() + randomIndex2);
    } else {
        destroyedSolution2.pathA.erase(destroyedSolution2.pathA.begin() + randomIndex1, destroyedSolution2.pathA.end());
        destroyedSolution2.pathA.erase(destroyedSolution2.pathA.begin(), destroyedSolution2.pathA.begin() + randomIndex2 - n);
    }
    n = destroyedSolution.pathB.size();
    randomIndex1 = rand() % n;
    randomIndex2 = randomIndex1 + k;
    if (randomIndex2 < n) {
        destroyedSolution2.pathB.erase(destroyedSolution2.pathB.begin() + randomIndex1, destroyedSolution2.pathB.begin() + randomIndex2);
    } else {
        destroyedSolution2.pathB.erase(destroyedSolution2.pathB.begin() + randomIndex1, destroyedSolution2.pathB.end());
        destroyedSolution2.pathB.erase(destroyedSolution2.pathB.begin(), destroyedSolution2.pathB.begin() + randomIndex2 - n);
    }
    return destroyedSolution2;
}

TSPSolution repair(const TSPData& data, const TSPSolution& solution) {
    TSPSolution repairedSolution = cycleAugmentation(data, solution);
    return repairedSolution;
}