#include "random_walk.hpp"


TSPSolution randomWalkVertices(const TSPData& data, TSPSolution startingSolution, int timeLimit) {
  TSPSolution bestSolution = startingSolution;
  TSPSolution currentSolution = startingSolution;
  auto startTime = std::chrono::high_resolution_clock::now();

  while (true) {
    std::pair<int, int> move;
    if (rand() % 2 == 0) {
      move = outsideMoves(currentSolution)[rand() % outsideMoves(currentSolution).size()];
      currentSolution.distance += calculateDeltaOutside(data, currentSolution, move.first, move.second);
      currentSolution = doOutsideMove(currentSolution, move.first, move.second);
    } else {
      if (rand() % 2 == 0) {
        move = insideMoves(currentSolution.pathA)[rand() % insideMoves(currentSolution.pathA).size()];
        currentSolution.distance += calculateDeltaInsideVertices(data, currentSolution, move.first, move.second, 0);
        currentSolution = doInsideMoveVertices(currentSolution, move.first, move.second, 0);
      } else {
        move = insideMoves(currentSolution.pathB)[rand() % insideMoves(currentSolution.pathB).size()];
        currentSolution.distance += calculateDeltaInsideVertices(data, currentSolution, move.first, move.second, 1);
        currentSolution = doInsideMoveVertices(currentSolution, move.first, move.second, 1);
      }
    }
    if (currentSolution.distance < bestSolution.distance) {
      bestSolution = currentSolution;
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    if (elapsedTime >= timeLimit) {
      break;
    }
  }
  return bestSolution;
}


TSPSolution randomWalkEdges(const TSPData& data, TSPSolution startingSolution, int timeLimit) {
  TSPSolution bestSolution = startingSolution;
  TSPSolution currentSolution = startingSolution;
  auto startTime = std::chrono::high_resolution_clock::now();

  while (true) {
    std::pair<int, int> move;
    if (rand() % 2 == 0) {
      move = outsideMoves(currentSolution)[rand() % outsideMoves(currentSolution).size()];
      currentSolution.distance += calculateDeltaOutside(data, currentSolution, move.first, move.second);
      currentSolution = doOutsideMove(currentSolution, move.first, move.second);
    } else {
      if (rand() % 2 == 0) {
        move = insideMoves(currentSolution.pathA)[rand() % insideMoves(currentSolution.pathA).size()];
        currentSolution.distance += calculateDeltaInsideEdges(data, currentSolution, move.first, move.second, 0);
        currentSolution = doInsideMoveEdges(currentSolution, move.first, move.second, 0);
      } else {
        move = insideMoves(currentSolution.pathB)[rand() % insideMoves(currentSolution.pathB).size()];
        currentSolution.distance += calculateDeltaInsideEdges(data, currentSolution, move.first, move.second, 1);
        currentSolution = doInsideMoveEdges(currentSolution, move.first, move.second, 1);
      }
    }
    if (currentSolution.distance < bestSolution.distance) {
      bestSolution = currentSolution;
    }
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
    if (elapsedTime >= timeLimit) {
      break;
    }
  }
  return bestSolution;
}