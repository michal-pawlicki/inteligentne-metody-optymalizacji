#include "nearest_neighbour.hpp"

TSPSolution nearestNeighbour(const TSPData& data) {
  TSPSolution solution;
  std::vector<bool> visited(data.coordinates.size(), false);

  srand(time(0));
  
  int startNodeA = rand() % data.coordinates.size(); 
  solution.pathA.push_back(startNodeA);
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
    std::pair<int, int> partialSolutionA = findBest(data, visited, solution.pathA);
    visited[partialSolutionA.second] = true;
    solution.pathA.insert(solution.pathA.begin() + partialSolutionA.first, partialSolutionA.second);
    
    std::pair<int, int> partialSolutionB = findBest(data, visited, solution.pathB);
    visited[partialSolutionB.second] = true;
    solution.pathB.insert(solution.pathB.begin() + partialSolutionB.first, partialSolutionB.second);    
  }

  solution.pathA.insert(solution.pathA.end(), solution.pathA[0]);
  solution.pathB.insert(solution.pathB.end(), solution.pathB[0]);

  return solution;
}

std::pair<int, int> findBest(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path ) {
  int bestDistance = 99999999;
  int bestIndex = -1;
  int bestNode = -1;

  for(int i = 0; i <= path.size(); i++) {
    for(int j = 0; j < data.coordinates.size(); j++) {
      if (!visited[j]) {
        std::vector<int> tmpPath = path;
        tmpPath.insert(tmpPath.begin() + i, j);
        int distance = calculateDistance(data, tmpPath);
       
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

int calculateDistance(const TSPData& data, const std::vector<int>& path) {
  int distance = 0;
  for (int i = 0; i < path.size() - 1; i++) {
    distance += data.distances[path[i]][path[i + 1]];
  }
  distance += data.distances[path[path.size() - 1]][path[0]];
  return distance;
}

void printSolution(const TSPSolution& solution) {
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