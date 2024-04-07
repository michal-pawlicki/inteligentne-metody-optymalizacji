#include "steepest.hpp"



TSPSolution steepestVertices(const TSPData& data, TSPSolution startingSolution) {
  while (true) {
    std::pair<int, int> bestOutsideMove = findBestOutsideMove(data, startingSolution);
    std::pair< int, std::pair<int, int> > bestInsideMove = findBestInsideMoveVertices(data, startingSolution);


    int deltaOutside = calculateDeltaOutside(data, startingSolution, bestOutsideMove.first, bestOutsideMove.second);
    int deltaInside = calculateDeltaInsideVertices(data, startingSolution, bestInsideMove.second.first, bestInsideMove.second.second, bestInsideMove.first);

    if ((deltaOutside <= deltaInside) && (deltaOutside < 0)) {
      startingSolution = doOutsideMove(startingSolution, bestOutsideMove.first, bestOutsideMove.second);
      startingSolution.distance += deltaOutside;
    } else if ((deltaInside < deltaOutside) && (deltaInside < 0)) {
      startingSolution = doInsideMoveVertices(startingSolution, bestInsideMove.second.first, bestInsideMove.second.second, bestInsideMove.first);
      startingSolution.distance += deltaInside;
    }
    else {
      break;
    }
  }
  return startingSolution;
}

TSPSolution steepestEdges(const TSPData& data, TSPSolution startingSolution) {
  while (true) {
    std::pair<int, int> bestOutsideMove = findBestOutsideMove(data, startingSolution);
    std::pair< int, std::pair<int, int> > bestInsideMove = findBestInsideMoveEdges(data, startingSolution);

    int deltaOutside = calculateDeltaOutside(data, startingSolution, bestOutsideMove.first, bestOutsideMove.second);
    int deltaInside = calculateDeltaInsideEdges(data, startingSolution, bestInsideMove.second.first, bestInsideMove.second.second, bestInsideMove.first);


    if ((deltaOutside <= deltaInside) && (deltaOutside < 0)) {
      startingSolution = doOutsideMove(startingSolution, bestOutsideMove.first, bestOutsideMove.second);
      startingSolution.distance += deltaOutside;
    } else if ((deltaInside < deltaOutside) && (deltaInside < 0)) {
      startingSolution = doInsideMoveEdges(startingSolution, bestInsideMove.second.first, bestInsideMove.second.second, bestInsideMove.first);
      startingSolution.distance += deltaInside;
    }
    else {
      break;
    }
  }
  return startingSolution;
}


std::pair<int, int> findBestOutsideMove(const TSPData& data, const TSPSolution& solution) {
  int bestDelta = 999999999;
  std::pair<int, int> bestMove = std::make_pair(-1, -1);
  for (auto move : outsideMoves(solution)) {
    int delta = calculateDeltaOutside(data, solution, move.first, move.second);
    if (delta < bestDelta) {
      bestDelta = delta;
      bestMove = move;
    }
  }
  return bestMove;
}

std::pair< int, std::pair<int, int> > findBestInsideMoveVertices(const TSPData& data, const TSPSolution& solution) {
  int bestDelta = 999999999;
  int pathIndex = 0;
  std::pair<int, int> bestMove = std::make_pair(-1, -1);
  for (auto move : insideMoves(solution.pathA)) {
    int deltaA = calculateDeltaInsideVertices(data, solution, move.first, move.second, 0);
    int deltaB = calculateDeltaInsideVertices(data, solution, move.first, move.second, 1);
    if (deltaA < bestDelta) {
      pathIndex = 0;
      bestDelta = deltaA;
      bestMove = move;
    }
    if (deltaB < bestDelta) {
      pathIndex = 1;
      bestDelta = deltaB;
      bestMove = move;
    }
  }
  return std::make_pair(pathIndex, bestMove);
}

std::pair< int, std::pair<int, int> > findBestInsideMoveEdges(const TSPData& data, const TSPSolution& solution) {
  int bestDelta = 999999999;
  int pathIndex = 0;
  std::pair<int, int> bestMove = std::make_pair(-1, -1);
  for (auto move : insideMoves(solution.pathA)) {
    int deltaA = calculateDeltaInsideEdges(data, solution, move.first, move.second, 0);
    int deltaB = calculateDeltaInsideEdges(data, solution, move.first, move.second, 1);
    if (deltaA < bestDelta) {
      pathIndex = 0;
      bestDelta = deltaA;
      bestMove = move;
    }
    if (deltaB < bestDelta) {
      pathIndex = 1;
      bestDelta = deltaB;
      bestMove = move;
    }
  }
  return std::make_pair(pathIndex, bestMove);
}