#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include "reader.hpp"
#include "iterated_local_search.hpp"
#include "multiple_start_local_search.hpp"
#include "large_scale_neighbourhood_search.hpp"
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

    auto start = std::chrono::high_resolution_clock::now();

    if(algorithm == "msls") {
        solution = multipleStartLocalSearch(data, 100);
    } else if(algorithm == "ils1") {
        solution = iteratedLocalSearch(data, 1000);
    } else if(algorithm == "ils2-1") {
        solution = largeScaleNeighbourhoodSearch(data, false, 1000);
    } else if(algorithm == "ils2-2") {
        solution = largeScaleNeighbourhoodSearch(data, true, 1000);
    } else if(algorithm == "steepest") {
        solution = steepestEdges(data, generateRandomSolution(data));
    } else if(algorithm == "cycle") {
        solution = cycleAugmentation(data, startNode);
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

    outFile2 << solution.numberOfIterations << std::endl;

    outFile2.close();

    return 0;
}