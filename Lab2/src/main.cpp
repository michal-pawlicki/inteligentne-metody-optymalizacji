#include <iostream>
#include <fstream>
#include "reader.hpp"

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <starting node> <data set> <starting algorithm>" << std::endl;
        return 1;
    }


    int startingNode = std::stoi(argv[1]);

    std::string dataSet = argv[2];

    std::string startingAlgorithm = argv[3];


    std::string filename = "../data/lab1/" + dataSet + "100";

    
    TSPData data = readTSPData(filename);

    TSPSolution solution = readTSPSolution("../data/lab2/" + dataSet + "/" + startingAlgorithm + "/solution_" + std::to_string(startingNode) + ".txt");

    std::cout << "Path A: ";
    for (int i = 0; i < solution.pathA.size(); i++) {
        std::cout << solution.pathA[i] << " ";
    }



    return 0;
}