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
      for (int j = 0; j < path.size(); j++) {
        if (i != j) {
          moves.push_back(std::make_pair(i, j));
        }
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


int calculateDeltaOutsideCache(const TSPData& data, const TSPSolution& solution, int i, int j) {
    std::vector<int> firstPath = solution.pathA;
    std::vector<int> secondPath = solution.pathB;
    int x1, x2, y1, y2, z1, z2;

    x1 = firstPath[(i - 1 + firstPath.size()) % firstPath.size()];
    y1 = firstPath[i];
    z1 = firstPath[(i + 1) % firstPath.size()];

    x2 = secondPath[(j - 1 + secondPath.size()) % secondPath.size()];
    y2 = secondPath[j];
    z2 = secondPath[(j + 1) % secondPath.size()];

    int delta = 0;
    delta -= data.distances[x1][y1];
    delta -= data.distances[y1][z1];
    delta -= data.distances[x2][y2];
    delta -= data.distances[y2][z2];

    delta += data.distances[x1][y2];
    delta += data.distances[y2][z1];
    delta += data.distances[x2][y1];
    delta += data.distances[y1][z2];

    Move move = createMove(x1, y1, x2, y2, outside, delta);
    move.m = z1;
    move.n = z2;


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

    if ( j < i) {
      std::swap(i, j);
    }

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


int calculateDeltaInsideEdgesCache(const TSPData& data, const TSPSolution& solution, int i, int j, int k, int l, int pathIndex) {
    int delta = 0;
    std::vector<int> path = pathIndex == 0 ? solution.pathA : solution.pathB;
    int a1, a2, b1, b2;
    a1 = path[i];
    a2 = path[j];
    b1 = path[k];
    b2 = path[l];


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
    if ( j < i) {
      std::swap(i, j);
    }
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

TSPSolution doInsideMoveEdgesCache(const TSPSolution& solution, int i, int j, int pathIndex) {
    TSPSolution newSolution = solution;
    if ( j < i) {
      std::swap(i, j);
    }
    if (pathIndex == 0) {
      if(i == 0 && j == newSolution.pathA.size() - 1) {
        std::swap(newSolution.pathA[i], newSolution.pathA[j]);
      } else {
        std::reverse(newSolution.pathA.begin() + i + 1, newSolution.pathA.begin() + j + 1);
      }
    } else {
      if(i == 0 && j == newSolution.pathB.size() - 1) {
        std::swap(newSolution.pathB[i], newSolution.pathB[j]);
      } else {
        std::reverse(newSolution.pathB.begin() + i+ 1, newSolution.pathB.begin() + j+ 1);
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

TSPSolution generateRandomSolution(const TSPData& data) {
  TSPSolution solution;
  std::vector<int> indices(data.coordinates.size());

  std::iota(indices.begin(), indices.end(), 0); 

  std::random_device rd;
  std::mt19937 eng(rd()); 
  std::shuffle(indices.begin(), indices.end(), eng); 
  
  std::vector <int> pathA = std::vector<int>(indices.begin(), indices.begin() + data.coordinates.size() / 2);
  std::vector <int> pathB = std::vector<int>(indices.begin() + data.coordinates.size() / 2 , indices.end());

  solution.pathA = pathA;
  solution.pathB = pathB;

  solution.distance = calculateDistanceCycle(data, pathA) + calculateDistanceCycle(data, pathB);
  return solution;
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

int findCityIndex(std::vector<int> path, int city) {
  auto it = std::find(path.begin(), path.end(), city);
  return std::distance(path.begin(), it);
}

Move createMove(int i, int j, int k, int l, moveType type, int delta) {
  Move move;
  move.i = i;
  move.j = j;
  move.k = k;
  move.l = l;
  move.type = type;
  move.delta = delta;

  return move;
}

int edgeExists(const TSPSolution& solution, int i, int j, int pathIndex) { //zwraca 0 gdy nie istnieje, 1 gdy istnieje w podanej kolejności, -1 gdy istnieje w odwrotnej
  std::vector<int> path = pathIndex == 0 ? solution.pathA : solution.pathB;
  for(int k = 0; k < path.size() - 1; k++) {
    int x = path[k];
    int y = path[k + 1];
    if (x == i && y == j) {
      return 1;
    }
    if (x == j && y == i) {
      return -1;
    }
  }
  int x = path.back();
  int y = path[0];
  if (x == i && y == j) {
    return 1;
  }
  if (x == j && y == i) {
    return -1;
  }
  return 0; 
}

std::pair<int, int> edgeExistsAnywhere(const TSPSolution& solution, int i, int j) { //zwraca parę indeks ścieżki i czy istnieje
  int existsA = edgeExists(solution, i, j, 0);
  if (existsA != 0) {
    return std::make_pair(0, existsA);
  }
  int existsB = edgeExists(solution, i, j, 1);
  if (existsB != 0) {
    return std::make_pair(1, existsB);
  }
  return std::make_pair(-1, 0);
}