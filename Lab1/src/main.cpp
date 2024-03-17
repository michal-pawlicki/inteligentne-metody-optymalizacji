#include <iostream>
#include <fstream>
#include "reader.hpp"
#include "cycle_augmentation.hpp"
#include "nearest_neighbour.hpp"
#include "two_regret.hpp"

int main(int argc, char* argv[]) {
    std::string filename = "../data/kroB100";

    int startNode = atoi(argv[1]);
    
    TSPData data = readTSPData(filename);

    TSPSolution solution_cycle = cycleAugmentation(data, startNode);

    TSPSolution solution_neighbour = nearestNeighbour(data, startNode);
    

    TSPSolution solution_regret = twoRegret(data, startNode);


    std::ofstream outFile("solution_nearest_neighbour.txt");

    outFile << "Distance: " << solution_neighbour.distance << std::endl;

    outFile << "Path A: ";
    for (int i = 0; i < solution_neighbour.pathA.size(); i++) {
        outFile << "(" << data.coordinates[solution_neighbour.pathA[i]].x << "," << data.coordinates[solution_neighbour.pathA[i]].y << ") ";
    }
    outFile << std::endl;

    outFile << "Path B: ";
    for (int i = 0; i < solution_neighbour.pathB.size(); i++) {
        outFile << "(" << data.coordinates[solution_neighbour.pathB[i]].x << "," << data.coordinates[solution_neighbour.pathB[i]].y << ") ";
    }
    outFile << std::endl;

    outFile.close();

     std::ofstream outFile2("solution_cycle_augmentation.txt");

    outFile2 << "Distance: " << solution_cycle.distance << std::endl;


    outFile2 << "Path A: ";
    for (int i = 0; i < solution_cycle.pathA.size(); i++) {
        outFile2 << "(" << data.coordinates[solution_cycle.pathA[i]].x << "," << data.coordinates[solution_cycle.pathA[i]].y << ") ";
    }
    outFile2 << std::endl;

    outFile2 << "Path B: ";
    for (int i = 0; i < solution_cycle.pathB.size(); i++) {
        outFile2 << "(" << data.coordinates[solution_cycle.pathB[i]].x << "," << data.coordinates[solution_cycle.pathB[i]].y << ") ";
    }
    outFile2 << std::endl;

    outFile2.close();



     std::ofstream outFile3("solution_two_regret.txt");

    outFile3 << "Distance: " << solution_regret.distance << std::endl;


    outFile3 << "Path A: ";
    for (int i = 0; i < solution_regret.pathA.size(); i++) {
        outFile3 << "(" << data.coordinates[solution_regret.pathA[i]].x << "," << data.coordinates[solution_regret.pathA[i]].y << ") ";
    }
    outFile3 << std::endl;

    outFile3 << "Path B: ";
    for (int i = 0; i < solution_regret.pathB.size(); i++) {
        outFile3 << "(" << data.coordinates[solution_regret.pathB[i]].x << "," << data.coordinates[solution_regret.pathB[i]].y << ") ";
    }
    outFile3 << std::endl;

    outFile3.close();

   

    // std::ofstream outFile1("metrics_nearest_neighbour.txt", std::ios_base::app);
    // outFile1 << startNode << " " << solution_neighbour.distance << std::endl;
    // outFile1.close();

    // std::ofstream outFile2("metrics_cycle_augmentation.txt", std::ios_base::app);
    // outFile2 << startNode << " " << solution_cycle.distance << std::endl;
    // outFile2.close();

    // std::ofstream outFile3("metrics_two_regret.txt", std::ios_base::app);
    // outFile3 << startNode << " " << solution_regret.distance << std::endl;
    // outFile3.close();

    return 0;
}