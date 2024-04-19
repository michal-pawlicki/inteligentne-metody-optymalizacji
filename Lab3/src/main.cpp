#include <iostream>
#include <fstream>
#include "reader.hpp"
#include "cycle_augmentation.hpp"
#include "steepest.hpp"

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <startingNode> <dataSet> <algorithm>" << std::endl;
        return 1;
    }
    
    int startNode = atoi(argv[1]);
    std::string dataSet = argv[2];
    std::string algorithm = argv[3];

    std::string filename = "../data/" + dataSet + "200";

    TSPData data = readTSPData(filename);
    TSPSolution solution;

    if(algorithm == "cycle") {
        solution = cycleAugmentation(data, startNode);
    } else if(algorithm == "steepest") {
        TSPSolution randomSolution = generateRandomSolution(data);
        solution = steepestEdges(data, randomSolution);
    } else {
        std::cerr << "Invalid algorithm" << std::endl;
        return 1;
    }


    std::ofstream outFile2("test_" + std::to_string(startNode) + ".txt");

    outFile2 << solution.distance << std::endl;


    for (int i = 0; i < solution.pathA.size(); i++) {
        outFile2 <<  solution.pathA[i] << " ";
    }
    outFile2 << std::endl;

    for (int i = 0; i < solution.pathB.size(); i++) {
        outFile2 << solution.pathB[i] << " "; 
    }
    outFile2 << std::endl;

    outFile2.close();

    return 0;
}