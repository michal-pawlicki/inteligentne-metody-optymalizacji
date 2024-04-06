#include <fstream>
#include <vector>
#include <sstream>
#include "reader.hpp"



TSPData readTSPData(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("File not found");
  }

  TSPData data;
  std::string line;

  while (std::getline(file, line)) {
        if (line == "EOF") {
            break;
        }

        std::istringstream iss(line);
        int id;
        double x, y;
        if (!(iss >> id >> x >> y)) {
            break;
        }

        Point point;
        point.x = x;
        point.y = y;

        data.coordinates.push_back(point);
    }

    data.distances.resize(data.coordinates.size(), std::vector<int>(data.coordinates.size(), 0));

    for (int i = 0; i < data.coordinates.size(); i++) {
        for (int j = i + 1; j < data.coordinates.size(); j++) {
            int x1 = data.coordinates[i].x;
            int y1 = data.coordinates[i].y;
            int x2 = data.coordinates[j].x;
            int y2 = data.coordinates[j].y;
            int distance = std::round(std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2)));
            data.distances[i][j] = distance;
            data.distances[j][i] = distance;
        }
    }

    return data;
}

TSPSolution readTSPSolution(const std::string& filename) {
    std::ifstream solutionFile(filename);
    if (!solutionFile.is_open()) {
        throw std::runtime_error("Solution file not found");
    }

    TSPSolution solution;
    std::string line;

    // Read distance
    if (!std::getline(solutionFile, line)) {
        throw std::runtime_error("Failed to read distance from solution file");
    }
    solution.distance = std::stoi(line);

    // Read path A
    if (!std::getline(solutionFile, line)) {
        throw std::runtime_error("Failed to read path A from solution file");
    }
    std::istringstream pathAStream(line);
    int index;
    while (pathAStream >> index) {
        solution.pathA.push_back(index);
    }

    // Read path B
    if (!std::getline(solutionFile, line)) {
        throw std::runtime_error("Failed to read path B from solution file");
    }
    std::istringstream pathBStream(line);
    while (pathBStream >> index) {
        solution.pathB.push_back(index);
    }

    return solution;

}


