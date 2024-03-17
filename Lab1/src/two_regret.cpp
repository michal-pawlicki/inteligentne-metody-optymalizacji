#include "two_regret.hpp"


TSPSolution twoRegret(const TSPData& data, const int startNodeA) {
  TSPSolution solution;
  std::vector<bool> visited(data.coordinates.size(), false);

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
    std::pair<int, int> partialSolutionA = findBestRegret(data, visited, solution.pathA);

    visited[partialSolutionA.second] = true;
    solution.pathA.insert(solution.pathA.begin() + partialSolutionA.first, partialSolutionA.second);
    
    std::pair<int, int> partialSolutionB = findBestRegret(data, visited, solution.pathB);
    visited[partialSolutionB.second] = true;
    solution.pathB.insert(solution.pathB.begin() + partialSolutionB.first, partialSolutionB.second);    
  }

  solution.distance = calculateDistanceRegret(data, solution.pathA) + calculateDistanceRegret(data, solution.pathB);
  solution.pathA.insert(solution.pathA.end(), solution.pathA[0]);
  solution.pathB.insert(solution.pathB.end(), solution.pathB[0]);


  return solution;
}

std::pair<int, int> findBestRegret(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path ) {
  std::vector<std::vector<int> > regret;

  for(int i = 0; i < data.coordinates.size(); i++) {
    if (!visited[i]) {
      int firstBest = 99999999;
      int secondBest = 99999999;
      int bestIndexLocal = -1;
      for (int j = 0; j < path.size() ; j++) {
        std::vector<int> tmpPath = path;
        tmpPath.insert(tmpPath.begin() + j, i);


        int distance = calculateDistanceRegret(data, tmpPath);

        if (distance < firstBest) {
          secondBest = firstBest;
          firstBest = distance;
          bestIndexLocal = j;
        } else if (distance < secondBest) {
          secondBest = distance;
        }

      }

      std::vector<int> tmp;
      tmp.push_back(bestIndexLocal);
      tmp.push_back(i);
      tmp.push_back(secondBest - firstBest);
      regret.push_back(tmp);
    }
  }

  int bestIndex = -1;
  int bestNode = -1;
  int maxRegret = -1;

  for (int i = 0; i < regret.size(); i++) {
    if (regret[i][2] > maxRegret) {
      maxRegret = regret[i][2];
      bestIndex = regret[i][0];
      bestNode = regret[i][1];
    }
  }
  
  return std::make_pair(bestIndex, bestNode);
}

int calculateDistanceRegret(const TSPData& data, const std::vector<int>& path) {
  int distance = 0;
  for (int i = 0; i < path.size() - 1; i++) {
    distance += data.distances[path[i]][path[i + 1]];
  }
  distance += data.distances[path.back()][path[0]];
  return distance;
}