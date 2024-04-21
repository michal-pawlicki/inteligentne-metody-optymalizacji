#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "reader.hpp"
#include "cycle_augmentation.hpp"
#include "steepest.hpp"
#include "candidate_moves.hpp"
#include "cache_moves.hpp"

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

    auto start = std::chrono::high_resolution_clock::now();

    if(algorithm == "cycle") {
        solution = cycleAugmentation(data, startNode);
    } else if(algorithm == "steepest") {
        TSPSolution randomSolution = generateRandomSolution(data);
        solution = steepestEdges(data, randomSolution);
    } else if(algorithm == "candidates") {
        TSPSolution randomSolution = generateRandomSolution(data);
        solution = candidatesEdges(data, randomSolution, 20);
    } else if(algorithm == "cache") {
        TSPSolution randomSolution = generateRandomSolution(data);
        solution = cacheEdges(data, randomSolution);
    }
    else {
        std::cerr << "Invalid algorithm" << std::endl;
        return 1;
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

    outFile2.close();

    return 0;
}