#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "reader.hpp"
#include "steepest.hpp"
#include "hybrid_evolution.hpp"

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <startingNode> <dataSet> <doLocalSearch>" << std::endl;
        return 1;
    }
    
    int startNode = atoi(argv[1]);
    std::string dataSet = argv[2];
    std::string doLocalSearch = argv[3];

    std::string filename = "../data/" + dataSet + "200";

    TSPData data = readTSPData(filename);
    TSPSolution solution;

    auto start = std::chrono::high_resolution_clock::now();

    std::string algorithm;

    if (doLocalSearch == "0") {
        solution = hybridEvolution(data, 20, false, 1000);
        algorithm = "noLocalSearch";
    } else {
        solution = hybridEvolution(data, 20, true, 1000);
        algorithm = "withLocalSearch";
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Elapsed time: " << elapsed.count() << " miliseconds" << std::endl;

    

    std::string dirPath = dataSet + "/" + algorithm;
    system(("mkdir -p " + dirPath).c_str());

    std::ofstream outFile2(dataSet + "/" + algorithm + "/" + std::to_string(startNode) + ".txt");

    outFile2 << solution.distance << std::endl;


    for (int i = 0; i < solution.pathA.size(); i++) {
        outFile2 <<  solution.pathA[i] << " ";
    }
    outFile2 << std::endl;

    for (int i = 0; i < solution.pathB.size(); i++) {
        outFile2 << solution.pathB[i] << " "; 
    }
    outFile2 << std::endl;

    outFile2 << elapsed.count() << std::endl;

    outFile2 << solution.numberOfIterations << std::endl;

    outFile2.close();

    return 0;
}