#include "greedy.hpp"
#include <iostream>


TSPSolution greedyVertices(const TSPData& data, TSPSolution startingSolution) {

    while (true) {
        srand(time(NULL));

        if (rand() % 2 == 0) {
          std::pair<int, int> outsideMove = findFirstOutsideMove(data, startingSolution);

          if (outsideMove.first == -1) {
            std::pair< int, std::pair<int, int> > insideMove = findFirstInsideMoveVertices(data, startingSolution);
            if (insideMove.first == -1) {
              break;
            } else {
              startingSolution = doInsideMoveVertices(startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
              startingSolution.distance -= calculateDeltaInsideVertices(data, startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
            }
          } else {
            startingSolution = doOutsideMove(startingSolution, outsideMove.first, outsideMove.second);
            startingSolution.distance -= calculateDeltaOutside(data, startingSolution, outsideMove.first, outsideMove.second);
          }
        } else {
          std::pair< int, std::pair<int, int> > insideMove = findFirstInsideMoveVertices(data, startingSolution);
          if (insideMove.first == -1) {
            std::pair<int, int> outsideMove = findFirstOutsideMove(data, startingSolution);
            if (outsideMove.first == -1) {
              break;
            } else {
              startingSolution = doOutsideMove(startingSolution, outsideMove.first, outsideMove.second);
              startingSolution.distance -= calculateDeltaOutside(data, startingSolution, outsideMove.first, outsideMove.second);
            }
          } else {
            startingSolution = doInsideMoveVertices(startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
            startingSolution.distance -= calculateDeltaInsideVertices(data, startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
          }
        }
    }
    return startingSolution;
}

TSPSolution greedyEdges(const TSPData& data, TSPSolution startingSolution) {

    while (true) {
        srand(time(0));

        if (rand() % 2 == 0) {
          std::pair<int, int> outsideMove = findFirstOutsideMove(data, startingSolution);
          if (outsideMove.first == -1) {
            std::pair< int, std::pair<int, int> > insideMove = findFirstInsideMoveEdges(data, startingSolution);
            if (insideMove.first == -1) {
              break;
            } else {
              startingSolution = doInsideMoveEdges(startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
              startingSolution.distance -= calculateDeltaInsideEdges(data, startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
            }
          } else {
            startingSolution = doOutsideMove(startingSolution, outsideMove.first, outsideMove.second);
            startingSolution.distance -= calculateDeltaOutside(data, startingSolution, outsideMove.first, outsideMove.second);
          }
        } else {
          std::pair< int, std::pair<int, int> > insideMove = findFirstInsideMoveEdges(data, startingSolution);
          if (insideMove.first == -1) {
            std::pair<int, int> outsideMove = findFirstOutsideMove(data, startingSolution);
            if (outsideMove.first == -1) {
              break;
            } else {
              startingSolution = doOutsideMove(startingSolution, outsideMove.first, outsideMove.second);
              startingSolution.distance -= calculateDeltaOutside(data, startingSolution, outsideMove.first, outsideMove.second);
            }
          } else {
            startingSolution = doInsideMoveEdges(startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
            startingSolution.distance -= calculateDeltaInsideEdges(data, startingSolution, insideMove.second.first, insideMove.second.second, insideMove.first);
          }
        }

    }
    return startingSolution;
}


std::pair<int, int> findFirstOutsideMove(const TSPData& data, const TSPSolution& solution) {
  std::pair<int, int> bestMove = std::make_pair(-1, -1);
  std::vector<std::pair<int, int> > moves = outsideMoves(solution);
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::shuffle(moves.begin(), moves.end(), rng);
  for (auto move : moves) {
    int delta = calculateDeltaOutside(data, solution, move.first, move.second);
    if (delta < 0) {
      return move;
    }
  }
  return bestMove;
}

std::pair< int, std::pair<int, int> > findFirstInsideMoveVertices(const TSPData& data, const TSPSolution& solution) {
  std::pair<int, int> bestMove = std::make_pair(-1, -1);
  std::vector<std::pair<int, int> > movesA = insideMoves(solution.pathA);
  std::vector<std::pair<int, int> > movesB = insideMoves(solution.pathB);
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::shuffle(movesA.begin(), movesA.end(), rng);
  std::shuffle(movesB.begin(), movesB.end(), rng);
  if(rand() % 2 == 0) {
    for (auto move : movesA) {
      int delta = calculateDeltaInsideVertices(data, solution, move.first, move.second, 0);
      if (delta < 0) {
        return std::make_pair(0, move);
      }
    }
    for (auto move : movesB) {
      int delta = calculateDeltaInsideVertices(data, solution, move.first, move.second, 1);
      if (delta < 0) {
        return std::make_pair(1, move);
      }
    }
  } else {
    for (auto move : movesB) {
      int delta = calculateDeltaInsideVertices(data, solution, move.first, move.second, 1);
      if (delta < 0) {
        return std::make_pair(1, move);
      }
    }
    for (auto move : movesA) {
      int delta = calculateDeltaInsideVertices(data, solution, move.first, move.second, 0);
      if (delta < 0) {
        return std::make_pair(0, move);
      }
    }
  }
  return std::make_pair(-1, bestMove);
}


std::pair< int, std::pair<int, int> > findFirstInsideMoveEdges(const TSPData& data, const TSPSolution& solution) {
  std::pair<int, int> bestMove = std::make_pair(-1, -1);
  std::vector<std::pair<int, int> > movesA = insideMoves(solution.pathA);
  std::vector<std::pair<int, int> > movesB = insideMoves(solution.pathB);
  std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::shuffle(movesA.begin(), movesA.end(), rng);
  std::shuffle(movesB.begin(), movesB.end(), rng);
  if(rand() % 2 == 0) {
    for (auto move : movesA) {
      int delta = calculateDeltaInsideEdges(data, solution, move.first, move.second, 0);
      if (delta < 0) {
        return std::make_pair(0, move);
      }
    }
    for (auto move : movesB) {
      int delta = calculateDeltaInsideEdges(data, solution, move.first, move.second, 1);
      if (delta < 0) {
        return std::make_pair(1, move);
      }
    }
  } else {
    for (auto move : movesB) {
      int delta = calculateDeltaInsideEdges(data, solution, move.first, move.second, 1);
      if (delta < 0) {
        return std::make_pair(1, move);
      }
    }
    for (auto move : movesA) {
      int delta = calculateDeltaInsideEdges(data, solution, move.first, move.second, 0);
      if (delta < 0) {
        return std::make_pair(0, move);
      }
    }
  }
  return std::make_pair(-1, bestMove);
}