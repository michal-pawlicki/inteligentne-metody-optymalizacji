#include "cycle_augmentation.hpp"


TSPSolution cycleAugmentation(const TSPData& data, const int startNodeA) {
  TSPSolution solution;
  std::vector<bool> visited(data.coordinates.size(), false);

  visited[startNodeA] = true;

  int startNodeB = -1;
  int maxDistance = -1;
  for (int i = 0; i < data.coordinates.size(); i++) {
    if (!visited[i]) {
      int distance = data.distances[startNodeA][i];
      if (distance > maxDistance) {
        maxDistance = distance;
        startNodeB = i;
      }
    }
  }
  solution.pathB.push_back(startNodeB);
  visited[startNodeB] = true;


  
  while(visited != std::vector<bool>(data.coordinates.size(), true)) {
    std::pair<int, int> partialSolutionA = findBestCycle(data, visited, solution.pathA);
    visited[partialSolutionA.second] = true;
    solution.pathA.insert(solution.pathA.begin() + partialSolutionA.first, partialSolutionA.second);
    
    std::pair<int, int> partialSolutionB = findBestCycle(data, visited, solution.pathB);
    visited[partialSolutionB.second] = true;
    solution.pathB.insert(solution.pathB.begin() + partialSolutionB.first, partialSolutionB.second);    
  }

  solution.distance = calculateDistanceCycle(data, solution.pathA) + calculateDistanceCycle(data, solution.pathB);
  solution.pathA.insert(solution.pathA.end(), solution.pathA[0]);
  solution.pathB.insert(solution.pathB.end(), solution.pathB[0]);


  return solution;
}

std::pair<int, int> findBestCycle(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path ) {
  int bestDistance = 99999999;
  int bestIndex = -1;
  int bestNode = -1;

  for(int i = 0; i <= path.size(); i++) {
    for(int j = 0; j < data.coordinates.size(); j++) {
      if (!visited[j]) {
         std::vector<int> tmpPath = path;
        tmpPath.insert(tmpPath.begin() + i, j);
        int distance = calculateDistanceCycle(data, tmpPath);
       
        if (distance < bestDistance) {
          bestDistance = distance;
          bestIndex = i;
          bestNode = j;
        }
      }
    }
  }
  
  return std::make_pair(bestIndex, bestNode);
}

int calculateDistanceCycle(const TSPData& data, const std::vector<int>& path) {
  int distance = 0;
  for (int i = 0; i < path.size(); i++) {
    distance += data.distances[path[i]-1][path[i + 1]-1];
  }
  distance += data.distances[path.back()][path[0]-1];
  return distance;
}

void printSolutionCycle(const TSPSolution& solution) {
  std::cout << "Path A: ";
  for (int node : solution.pathA) {
    std::cout << node << " ";
  }
  std::cout << std::endl;

  std::cout << "Path B: ";
  for (int node : solution.pathB) {
    std::cout << node << " ";
  }
  std::cout << std::endl;
}