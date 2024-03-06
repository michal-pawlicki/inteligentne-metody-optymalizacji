#include <iostream>
#include "reader.hpp"
#include "nearest_neighbour.hpp"

int main() {
    std::string filename = "../data/kroA100";
    
    TSPData data = readTSPData(filename);

    TSPSolution solution = nearestNeighbour(data);

    std::cout << "Path A: ";
    for (int i = 0; i < solution.pathA.size(); i++) {
        std::cout << solution.pathA[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Path B: ";
    for (int i = 0; i < solution.pathB.size(); i++) {
        std::cout << solution.pathB[i] << " ";
    }
    std::cout << std::endl;


    return 0;
}