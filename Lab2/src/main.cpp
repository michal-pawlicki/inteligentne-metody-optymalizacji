#include <iostream>
#include <fstream>
#include <chrono>
#include "reader.hpp"
#include "steepest.hpp"
#include "random_walk.hpp"
#include "greedy.hpp"

int main(int argc, char* argv[]) {

    if (argc != 7) {
        std::cerr << "Usage: " << argv[0] << " <startingNode> <dataSet> <startingAlgorithm> <typeOfNeighbourhood> <typeOfLocalSearch> <nameOfOutputFile>" << std::endl;
        return 1;
    }

    int startingNode = std::stoi(argv[1]);

    std::string dataSet = argv[2];

    std::string startingAlgorithm = argv[3];

    std::string typeOfNeighbourhood = argv[4];

    std::string typeOfLocalSearch = argv[5];

    std::string nameOfOutputFile = argv[6];



    std::string filename = "../data/lab1/" + dataSet + "100";

    
    TSPData data = readTSPData(filename);

    TSPSolution solution = readTSPSolution("../data/lab2/" + dataSet + "/" + startingAlgorithm + "/solution_" + std::to_string(startingNode) + ".txt");

    solution.distance = calculateDistanceCycle(data, solution.pathA) + calculateDistanceCycle(data, solution.pathB);

    TSPSolution newSolution;



    auto start = std::chrono::high_resolution_clock::now();


    if (typeOfLocalSearch == "steepest") {
        if (typeOfNeighbourhood == "vertices") {
            newSolution = steepestVertices(data, solution);
        } else {
            newSolution = steepestEdges(data, solution);
        }
    } else if (typeOfLocalSearch == "random_walk") {
        if (typeOfNeighbourhood == "vertices") {
            newSolution = randomWalkVertices(data, solution, 250);
        } else {
            newSolution = randomWalkEdges(data, solution, 250);
        }
    } else if (typeOfLocalSearch == "greedy") {
        if (typeOfNeighbourhood == "vertices") {
            newSolution = greedyVertices(data, solution);
        } else {
            newSolution = greedyEdges(data, solution);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::ofstream file;
    file.open(nameOfOutputFile);
    file << newSolution.distance << std::endl;
    for (int i = 0; i < newSolution.pathA.size(); i++) {
        file << newSolution.pathA[i] << " ";
    }
    file << std::endl;
    for (int i = 0; i < newSolution.pathB.size(); i++) {
        file << newSolution.pathB[i] << " ";
    }
    file << std::endl;
    file << duration << std::endl;



    return 0;
}