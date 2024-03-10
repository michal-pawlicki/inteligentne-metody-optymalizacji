#include <iostream>
#include <fstream>
#include "reader.hpp"
#include "nearest_neighbour.hpp"

int main() {
    std::string filename = "../data/kroA100";
    
    TSPData data = readTSPData(filename);

    TSPSolution solution = nearestNeighbour(data);

    std::ofstream outFile("solution_nearest_neighbour.txt");

    outFile << "Path A: ";
    for (int i = 0; i < solution.pathA.size(); i++) {
        outFile << "(" << data.coordinates[solution.pathA[i]].x << "," << data.coordinates[solution.pathA[i]].y << ") ";
    }
    outFile << std::endl;

    outFile << "Path B: ";
    for (int i = 0; i < solution.pathB.size(); i++) {
        outFile << "(" << data.coordinates[solution.pathB[i]].x << "," << data.coordinates[solution.pathB[i]].y << ") ";
    }
    outFile << std::endl;

    outFile.close();

    return 0;
}