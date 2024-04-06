#include "helpers.hpp"
#include <iostream>

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

int calculateDeltaOutside(const TSPData& data, const TSPSolution& solution, int i, int j) {
    int delta = 0;
    delta -= data.distances[solution.pathA[i]][solution.pathA[(i + 1) % solution.pathA.size()]];
    delta -= data.distances[solution.pathA[(i - 1) % solution.pathA.size()]][solution.pathA[i]];
    delta -= data.distances[solution.pathB[j]][solution.pathB[(j + 1) % solution.pathB.size()]];
    delta -= data.distances[solution.pathB[(j - 1) % solution.pathB.size()]][solution.pathB[j]];

    delta += data.distances[solution.pathA[i]][solution.pathB[(j + 1) % solution.pathB.size()]];
    delta += data.distances[solution.pathB[(j - 1) % solution.pathB.size()]][solution.pathA[i]];
    delta += data.distances[solution.pathB[j]][solution.pathA[(i + 1) % solution.pathA.size()]];
    delta += data.distances[solution.pathA[(i - 1) % solution.pathA.size()]][solution.pathB[j]];

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

    if ( i == 0 & j == path.size() - 1) {
      delta += data.distances[path[i]][path[(j - 1 + path.size()) % path.size()]];
      delta += data.distances[path[(i + 1) % path.size()]][path[j]];
      delta -= data.distances[path[i]][path[(i + 1) % path.size()]];
      delta -= data.distances[path[j]][path[(j - 1 + path.size()) % path.size()]];
    } else {
      delta += data.distances[path[(i-1 + path.size()) % path.size()]][path[j]];
      delta += data.distances[path[i]][path[(j + 1) % path.size()]];
      delta -= data.distances[path[(i-1 + path.size()) % path.size()]][path[i]];
      delta -= data.distances[path[j]][path[(j + 1) % path.size()]];
    }

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
      } 
      std::reverse(newSolution.pathA.begin() + i, newSolution.pathA.begin() + j + 1);
    } else {
      if(i == 0 && j == newSolution.pathB.size() - 1) {
        std::swap(newSolution.pathA[i], newSolution.pathA[j]);
      } 
      std::reverse(newSolution.pathB.begin() + i, newSolution.pathB.begin() + j + 1);
    }
    return newSolution;
}