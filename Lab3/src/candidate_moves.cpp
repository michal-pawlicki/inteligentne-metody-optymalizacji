#include "candidate_moves.hpp"

TSPSolution candidatesEdges(const TSPData& data, const TSPSolution& solution, int k) {
  TSPSolution result = solution;
  std::vector<std::pair<int, int> > cityIndexes = candidateCityIndexes(data, k);
  while (true) {
    int bestDelta = 0;
    bool isBestMoveInside = false;
    int bestPathIndex = 0;
    std::pair<int, int> bestMove = std::make_pair(-1, -1);

    for (auto citiesPair : cityIndexes) {
      int delta = 0;
      std::pair<int, int> pathIndexes = areCitiesInSamePath(result, citiesPair.first, citiesPair.second);
      // std::cout<<citiesPair.first<<" "<<citiesPair.second<<std::endl;
      // std::cout<<pathIndexes.first<<" "<<pathIndexes.second<<std::endl;
      std::pair<int, int> move;
      if(pathIndexes.first == pathIndexes.second) {
        move = findCities(result, citiesPair.first, citiesPair.second);
        // std::cout<<move.first<<" "<<move.second<<std::endl;
        delta = calculateDeltaInsideEdges(data, result, move.first, move.second, pathIndexes.first);
      } else {
        move = findCities(result, citiesPair.first, citiesPair.second);
        // std::cout<<move.first<<" "<<move.second<<std::endl;
        move.second = (move.second + 1) % result.pathB.size();
        delta = calculateDeltaOutside(data, result, move.first, move.second);
      }
      // std::cout<<delta<<std::endl;
      if (delta < bestDelta) {
        bestDelta = delta;
        bestMove = move;
        isBestMoveInside = pathIndexes.first == pathIndexes.second;
        bestPathIndex = pathIndexes.first;
      }
      // std::cout<<"-----------------"<<std::endl;
    }
    
    if (bestDelta < 0) {
      result.distance += bestDelta;
      if (isBestMoveInside) {
        // std::cout<<"INSIDE MOVE"<<std::endl;
        // std::cout<<bestMove.first<<" "<<bestMove.second<<" "<<bestPathIndex<<std::endl;
        result = doInsideMoveEdges(result, bestMove.first, bestMove.second, bestPathIndex);
      } else {
        // std::cout<<"OUTSIDE MOVE"<<std::endl;
        // std::cout<<bestMove.first<<" "<<bestMove.second<<" "<<bestPathIndex<<std::endl;
        result = doOutsideMove(result, bestMove.first, bestMove.second);
      }
    }
    else {
      break;
    }
    // std::cout<<result.distance<<std::endl;
    // printSolutionCycle(result);
  }
  return result;
}


std::vector<std::pair<int, int> > candidateCityIndexes(const TSPData& data, int k) {
    std::vector<std::pair<int, int> > cityIndexes;
    for (int i = 0; i < data.distances.size(); i++) {
      std::vector<std::pair<int, int> > closestCities;
      for (int j = 0; j < data.distances.size(); j++) {
        if (i != j) {
          closestCities.push_back(std::make_pair(data.distances[i][j], j));
        }
      }
      std::sort(closestCities.begin(), closestCities.end());
      for (int l = 0; l < k; l++) {
        cityIndexes.push_back(std::make_pair(i, closestCities[l].second));
      }
    } 
    return cityIndexes;  
}

std::pair<int, int> findCities(const TSPSolution& solution, int cityA, int cityB) {
  int indexA = findCityIndex(solution.pathA, cityA);
  int indexB = findCityIndex(solution.pathA, cityB);
  if (indexA == solution.pathA.size()) {
    indexA = findCityIndex(solution.pathB, cityA);
  }
  if (indexB == solution.pathA.size()) {
    indexB = findCityIndex(solution.pathB, cityB);
  }
  return std::make_pair(indexA, indexB);
}

std::pair<int, int> areCitiesInSamePath(const TSPSolution& solution, int cityA, int cityB) {
  bool isCityAInPathA = std::find(solution.pathA.begin(), solution.pathA.end(), cityA) != solution.pathA.end();
  bool isCityBInPathA = std::find(solution.pathA.begin(), solution.pathA.end(), cityB) != solution.pathA.end();
  
  return std::make_pair(isCityAInPathA ? 0 : 1, isCityBInPathA ? 0 : 1);
}