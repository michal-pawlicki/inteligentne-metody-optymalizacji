#include "helpers.hpp"

std::vector<std::pair<int, int> > outsideMoves(const TSPSolution& solution) {
    std::vector<std::pair<int, int> > moves;
    for (int i = 0; i < solution.pathA.size(); i++) {
      for (int j = 0; j < solution.pathB.size(); j++) {
        moves.push_back(std::make_pair(i, j));
      }
    }
    return moves;
}

std::vector<std::pair<int, int> > insideMoves(const std::vector<int> path) {
    std::vector<std::pair<int, int> > moves;
    for (int i = 0; i < path.size(); i++) {
      for (int j = i + 1; j < path.size(); j++) {
        moves.push_back(std::make_pair(i, j));
      }
    }
    return moves;
}

int calculateSingleDeltaOutside(const TSPData& data, const std::vector<int> path, int i, int cityIndex) {
    int delta = 0;
    int a1 = path[(i - 1 + path.size()) % path.size()];
    int a2 = path[i];
    int a3 = path[(i + 1) % path.size()];

    delta -= data.distances[a1][a2];
    delta -= data.distances[a2][a3];
    delta += data.distances[a1][cityIndex];
    delta += data.distances[cityIndex][a3];

    return delta;
}


int calculateDeltaOutside(const TSPData& data, const TSPSolution& solution, int i, int j) {
    int delta = 0;
    
    delta += calculateSingleDeltaOutside(data, solution.pathA, i, solution.pathB[j]);
    delta += calculateSingleDeltaOutside(data, solution.pathB, j, solution.pathA[i]);

    return delta;
}

int calculateDeltaInsideVertices(const TSPData& data, const TSPSolution& solution, int i, int j, int pathIndex) {
    int delta = 0;
    std::vector<int> path = pathIndex == 0 ? solution.pathA : solution.pathB;

    int a1 = path[(i - 1 + path.size()) % path.size()];
    int a2 = path[i];
    int a3 = path[(i + 1) % path.size()];

    int b1 = path[(j - 1 + path.size()) % path.size()];
    int b2 = path[j];
    int b3 = path[(j + 1) % path.size()];

    if (j-1 == i) {
      delta += data.distances[a1][b2];
      delta += data.distances[a2][b3];
      delta -= data.distances[a1][a2];
      delta -= data.distances[b2][b3];

      return delta;
    } else if ( i == 0 && j == path.size() - 1) {
      delta += data.distances[b2][a3];
      delta += data.distances[b1][a2];
      delta -= data.distances[a2][a3];
      delta -= data.distances[b1][b2];

      return delta;
    } else {
      delta += data.distances[a1][b2];
      delta += data.distances[a3][b2];
      delta += data.distances[b1][a2];
      delta += data.distances[b3][a2];
      delta -= data.distances[a1][a2];
      delta -= data.distances[a2][a3];
      delta -= data.distances[b1][b2];
      delta -= data.distances[b2][b3];

      return delta;
    
    }
}

int calculateDeltaInsideEdges(const TSPData& data, const TSPSolution& solution, int i, int j, int pathIndex) {
    int delta = 0;
    std::vector<int> path = pathIndex == 0 ? solution.pathA : solution.pathB;

    int a1, a2, b1, b2;

    if ( i == 0 & j == path.size() - 1) {
      a1 = path[i];
      a2 = path[(i + 1) % path.size()];
      b1 = path[j-1];
      b2 = path[j];
    } else {
      a1 = path[(i - 1 + path.size()) % path.size()];
      a2 = path[i];
      b1 = path[j];
      b2 = path[(j + 1) % path.size()];
    }

    delta += data.distances[a1][b1];
    delta += data.distances[a2][b2];
    delta -= data.distances[a1][a2];
    delta -= data.distances[b1][b2];
  
    return delta;
}
    


TSPSolution doOutsideMove(const TSPSolution& solution, int i, int j) {
    TSPSolution newSolution = solution;
    std::swap(newSolution.pathA[i], newSolution.pathB[j]);
    return newSolution;
}

TSPSolution doInsideMoveVertices(const TSPSolution& solution, int i, int j, int pathIndex) {
    TSPSolution newSolution = solution;
    if (pathIndex == 0) {
      std::swap(newSolution.pathA[i], newSolution.pathA[j]);
    } else {
      std::swap(newSolution.pathB[i], newSolution.pathB[j]);
    }
    return newSolution;
}

TSPSolution doInsideMoveEdges(const TSPSolution& solution, int i, int j, int pathIndex) {
    TSPSolution newSolution = solution;
    if (pathIndex == 0) {
      if(i == 0 && j == newSolution.pathA.size() - 1) {
        std::swap(newSolution.pathA[i], newSolution.pathA[j]);
      } else {
        std::reverse(newSolution.pathA.begin() + i, newSolution.pathA.begin() + j + 1);
      }
    } else {
      if(i == 0 && j == newSolution.pathB.size() - 1) {
        std::swap(newSolution.pathB[i], newSolution.pathB[j]);
      } else {
        std::reverse(newSolution.pathB.begin() + i, newSolution.pathB.begin() + j + 1);
      }
    }
    return newSolution;
}

int calculateDistanceCycle(const TSPData& data, const std::vector<int>& path) {
  int distance = 0;
  for (int i = 0; i < path.size(); i++) {
    distance += data.distances[path[i]][path[i + 1]];
  }
  distance += data.distances[path.back()][path[0]];
  return distance;
}