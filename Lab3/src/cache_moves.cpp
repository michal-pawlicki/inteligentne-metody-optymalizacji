#include "cache_moves.hpp"


TSPSolution cacheEdges(const TSPData& data, const TSPSolution& solution) {
    TSPSolution newSolution = solution;
    std::vector<Move> moves = generateMoves(data, newSolution);
    std::sort(moves.begin(), moves.end(), compareMoves);
    
    while(true) {
      Move bestMove;
      bestMove.type = none;
      int toRemove = 0;
      for (auto move : moves) {
        if (move.type == insideEdges) {
          std::pair<int, int> edgeExists1 = edgeExistsAnywhere(newSolution, move.i, move.j);
          std::pair<int, int> edgeExists2 = edgeExistsAnywhere(newSolution, move.k, move.l);
          if (edgeExists1.first != edgeExists2.first || edgeExists1.second == 0 || edgeExists2.second == 0) {
            toRemove += 1;
          } else if(edgeExists1.second == 1 && edgeExists2.second == 1) {
            // std::cout<<"To remove and to do"<<std::endl;
            // std::cout<<move.i<<" "<<move.j<<" "<<move.k<<" "<<move.l<<std::endl;
            // std::cout<<edgeExists1.first<<" "<<edgeExists2.first<<" "<<edgeExists1.second<<" "<<edgeExists2.second<<std::endl;
            toRemove += 1;
            bestMove = move;
            break;
          } else if (edgeExists1.second == -1 && edgeExists2.second == -1) {
            toRemove += 1;
            bestMove = createMove(move.j, move.i, move.l, move.k, insideEdges, move.delta);
            break;
          }
        } else if(move.type == outside) {
          int x1, x2, y1, y2, z1, z2;
          x1 = move.i;
          y1 = move.j;
          z1 = move.k;
          x2 = move.l;
          y2 = move.m;
          z2 = move.n;

          int edgeExists1 = edgeExists(newSolution, x1, y1, 0);
          int edgeExists2 = edgeExists(newSolution, y1, z1, 0);
          int edgeExists3 = edgeExists(newSolution, x2, y2, 1);
          int edgeExists4 = edgeExists(newSolution, y2, z2, 1);

          if(edgeExists1 == 0 || edgeExists2 == 0 || edgeExists3 == 0 || edgeExists4 == 0) {
            toRemove += 1;
          } else if(edgeExists1 == edgeExists2 && edgeExists3 == edgeExists4) {
            toRemove += 1;
            bestMove = move;
            break;
          }
        }
      }
      if (bestMove.type == none) {
        break;
      }
      for(int i = 0; i < toRemove; i++) {
        moves.erase(moves.begin());
      }
      

      if (bestMove.type == insideEdges) {
        int i = findCityIndex(newSolution.pathA, bestMove.i);
        int j = findCityIndex(newSolution.pathA, bestMove.k);
        int pathIndex = 0;
        if(i == newSolution.pathA.size()) {
          i = findCityIndex(newSolution.pathB, bestMove.i);
          j = findCityIndex(newSolution.pathB, bestMove.k);
          pathIndex = 1;
        }
        newSolution = doInsideMoveEdgesCache(newSolution, i, j, pathIndex);
      } else if (bestMove.type == outside) {
        newSolution = doOutsideMove(newSolution, findCityIndex(newSolution.pathA, bestMove.j), findCityIndex(newSolution.pathB, bestMove.m));        
      }

      newSolution.distance += bestMove.delta;
      // std::cout<<"Distance: "<<newSolution.distance<<std::endl;

      // std::cout<<"Moves size: "<<moves.size()<<std::endl;
      std::vector<Move> newMoves = generateNewMoves(data, newSolution, bestMove); //TODO: generateNewMoves
      moves.insert(moves.end(), newMoves.begin(), newMoves.end());
      std::sort(moves.begin(), moves.end(), compareMoves);
      moves.erase(std::unique(moves.begin(), moves.end()), moves.end());
      // std::cout<<"Moves size: "<<moves.size()<<std::endl;
      
    }
    
    return newSolution;
}

std::vector<Move> generateMoves(const TSPData& data, const TSPSolution& solution) {
    std::vector<Move> moves;
    for (auto move : insideMoves(solution.pathA)) {
      int i = move.first;
      int j = (move.first + 1) % solution.pathA.size();
      int k = move.second;
      int l = (move.second + 1) % solution.pathA.size();
      int deltaA = calculateDeltaInsideEdgesCache(data, solution, i, j, k, l, 0);
      int deltaB = calculateDeltaInsideEdgesCache(data, solution, i, j, k, l, 1);

      if (deltaA < 0) {
        moves.push_back(createMove(solution.pathA[i], solution.pathA[j], solution.pathA[k], solution.pathA[l], insideEdges, deltaA));
      }
      if (deltaB < 0) {
        moves.push_back(createMove(solution.pathB[i], solution.pathB[j], solution.pathB[k], solution.pathB[l], insideEdges, deltaB));
      }
    }
    for (auto move : outsideMoves(solution)) {
      int delta = calculateDeltaOutside(data, solution, move.first, move.second);
      if (delta < 0) {
        int x1 = solution.pathA[(move.first - 1) % solution.pathA.size()];
        int y1 = solution.pathA[move.first];
        int z1 = solution.pathA[(move.first + 1) % solution.pathA.size()];
        int x2 = solution.pathB[(move.second - 1) % solution.pathB.size()];
        int y2 = solution.pathB[move.second];
        int z2 = solution.pathB[(move.second + 1) % solution.pathB.size()];
        Move move;
        move.delta = delta;
        move.i = x1;
        move.j = y1;
        move.k = z1;
        move.l = x2;
        move.m = y2;
        move.n = z2;
        move.type = outside;
        moves.push_back(move);
      }
    }

    return moves;
}


bool compareMoves(const Move& move1, const Move& move2) {
    return move1.delta < move2.delta;
}

std::vector<Move> generateNewMoves(const TSPData& data, const TSPSolution& solution, Move move){ //TODO: generateNewMoves
    std::vector<Move> moves;
    if(move.type == insideEdges) {
      std::vector<int> path = findCityIndex(solution.pathA, move.i) == solution.pathA.size() ? solution.pathB : solution.pathA;
      int pathIndex = findCityIndex(solution.pathA, move.i) == solution.pathA.size() ? 1 : 0;
      int i = findCityIndex(path, move.i);
      int j = findCityIndex(path, move.j);
      int k = findCityIndex(path, move.k);
      int l = findCityIndex(path, move.l);
      // printSolutionCycle(solution);
      // std::cout<<"------------"<<std::endl;
      // std::cout<< move.i<<" "<<move.j<<" "<<move.k<<" "<<move.l<<std::endl;
      // std::cout<< i<<" "<<j<<" "<<k<<" "<<l<<std::endl;
      for(int d = 1; d < path.size() - 2; d++) {
        int firstIndex = (i + d) % path.size();
        int secondIndex = (i + d + 1) % path.size();
        int thirdIndex = (j + d) % path.size();
        int fourthIndex = (j + d + 1) % path.size();

        int firstDelta = calculateDeltaInsideEdgesCache(data, solution, firstIndex, secondIndex, i, k, pathIndex);
        int secondDelta = calculateDeltaInsideEdgesCache(data, solution, thirdIndex, fourthIndex, j, l, pathIndex);

        if(firstDelta < 0) {
          // std::cout<<"Found good inside move first"<<std::endl;
          // std::cout<<path[firstIndex]<<" "<<path[secondIndex]<<" "<<path[i]<<" "<<path[k]<<std::endl;
          moves.push_back(createMove(path[firstIndex], path[secondIndex], path[i], path[k], insideEdges, firstDelta));
        }
        if(secondDelta < 0) {
          // std::cout<<"Found good inside move second"<<std::endl;
          // std::cout<<path[thirdIndex]<<" "<<path[fourthIndex]<<" "<<path[j]<<" "<<path[l]<<std::endl;
          moves.push_back(createMove(path[thirdIndex], path[fourthIndex], path[j], path[l], insideEdges, secondDelta));
        }
      }
      if(pathIndex == 0) {
        for(int d=0; d<solution.pathA.size(); d++) {
          int deltaI = calculateDeltaOutside(data, solution, i, d);
          int deltaJ = calculateDeltaOutside(data, solution, j, d);
          int deltaK = calculateDeltaOutside(data, solution, k, d);
          int deltaL = calculateDeltaOutside(data, solution, l, d);
          if(deltaI < 0) {
            Move move;
            move.delta = deltaI;
            move.i = solution.pathA[(i - 1) % solution.pathA.size()];
            move.j = solution.pathA[i];
            move.k = solution.pathA[(i + 1) % solution.pathA.size()];
            move.l = solution.pathB[(d-1) % solution.pathA.size()];
            move.m = solution.pathB[d];
            move.n = solution.pathB[(d + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
          if(deltaJ < 0) {
            Move move;
            move.delta = deltaJ;
            move.i = solution.pathA[(j - 1) % solution.pathA.size()];
            move.j = solution.pathA[j];
            move.k = solution.pathA[(j + 1) % solution.pathA.size()];
            move.l = solution.pathB[(d-1) % solution.pathA.size()];
            move.m = solution.pathB[d];
            move.n = solution.pathB[(d + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
          if(deltaK < 0) {
            Move move;
            move.delta = deltaK;
            move.i = solution.pathA[(k - 1) % solution.pathA.size()];
            move.j = solution.pathA[k];
            move.k = solution.pathA[(k + 1) % solution.pathA.size()];
            move.l = solution.pathB[(d-1) % solution.pathA.size()];
            move.m = solution.pathB[d];
            move.n = solution.pathB[(d + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
          if(deltaL < 0) {
            Move move;
            move.delta = deltaL;
            move.i = solution.pathA[(l - 1) % solution.pathA.size()];
            move.j = solution.pathA[l];
            move.k = solution.pathA[(l + 1) % solution.pathA.size()];
            move.l = solution.pathB[(d-1) % solution.pathA.size()];
            move.m = solution.pathB[d];
            move.n = solution.pathB[(d + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
        }
      } else if(pathIndex == 1){
        for(int d=0; d<solution.pathA.size(); d++) {
          int deltaI = calculateDeltaOutside(data, solution, d, i);
          int deltaJ = calculateDeltaOutside(data, solution, d, j);
          int deltaK = calculateDeltaOutside(data, solution, d, k);
          int deltaL = calculateDeltaOutside(data, solution, d, l);
          if(deltaI < 0) {
            Move move;
            move.delta = deltaI;
            move.i = solution.pathA[(d - 1) % solution.pathA.size()];
            move.j = solution.pathA[d];
            move.k = solution.pathA[(d + 1) % solution.pathA.size()];
            move.l = solution.pathB[(i-1) % solution.pathA.size()];
            move.m = solution.pathB[i];
            move.n = solution.pathB[(i + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
          if(deltaJ < 0) {
            Move move;
            move.delta = deltaJ;
            move.i = solution.pathA[(d - 1) % solution.pathA.size()];
            move.j = solution.pathA[d];
            move.k = solution.pathA[(d + 1) % solution.pathA.size()];
            move.l = solution.pathB[(j-1) % solution.pathA.size()];
            move.m = solution.pathB[j];
            move.n = solution.pathB[(j + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
          if(deltaK < 0) {
            Move move;
            move.delta = deltaK;
            move.i = solution.pathA[(d - 1) % solution.pathA.size()];
            move.j = solution.pathA[d];
            move.k = solution.pathA[(d + 1) % solution.pathA.size()];
            move.l = solution.pathB[(k-1) % solution.pathA.size()];
            move.m = solution.pathB[k];
            move.n = solution.pathB[(k + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
          if(deltaL < 0) {
            Move move;
            move.delta = deltaL;
            move.i = solution.pathA[(d - 1) % solution.pathA.size()];
            move.j = solution.pathA[d];
            move.k = solution.pathA[(d + 1) % solution.pathA.size()];
            move.l = solution.pathB[(l-1) % solution.pathA.size()];
            move.m = solution.pathB[l];
            move.n = solution.pathB[(l + 1) % solution.pathA.size()];
            move.type = outside;
            moves.push_back(move);
          }
        }
      }

    } else if(move.type == outside) {
      int indexA = findCityIndex(solution.pathA, move.m);
      int indexB = findCityIndex(solution.pathB, move.j);

      for(int i = 0; i < solution.pathA.size(); i++) {
        int deltaA = calculateDeltaOutside(data, solution, indexA, i);
        int deltaB = calculateDeltaOutside(data, solution, i, indexB);
        if(deltaA < 0) {
          Move move;
          move.delta = deltaA;
          move.i = (indexA - 1) % solution.pathA.size();
          move.j = indexA;
          move.k = (indexA + 1) % solution.pathA.size();
          move.l = (i - 1) % solution.pathB.size();
          move.m = i;
          move.n = (i + 1) % solution.pathB.size();
          move.type = outside;
          moves.push_back(move);
        }
        if(deltaB < 0) {
          Move move;
          move.delta = deltaB;
          move.i = (i - 1) % solution.pathA.size();
          move.j = i;
          move.k = (i + 1) % solution.pathA.size();
          move.l = (indexB - 1) % solution.pathB.size();
          move.m = indexB;
          move.n = (indexB + 1) % solution.pathB.size();
          move.type = outside;
          moves.push_back(move);
        }
      }

      for(int d = 1; d < solution.pathA.size() - 2; d++) {
        int firstIndex = (indexA + d) % solution.pathA.size();
        int secondIndex = (indexA + d + 1) % solution.pathA.size();
        int thirdIndex = (indexB + d) % solution.pathA.size();
        int fourthIndex = (indexB + d + 1) % solution.pathA.size();
        

        int firstDelta = calculateDeltaInsideEdgesCache(data, solution, firstIndex, secondIndex, indexA, (indexA + 1)%solution.pathA.size(), 0);
        int secondDelta = calculateDeltaInsideEdgesCache(data, solution, thirdIndex, fourthIndex, indexB, (indexB + 1)%solution.pathB.size(), 1);

        if(firstDelta < 0) {
          moves.push_back(createMove(solution.pathA[firstIndex], solution.pathA[secondIndex], solution.pathA[indexA], solution.pathA[(indexA + 1)%solution.pathA.size()], insideEdges, firstDelta));
        }
        if(secondDelta < 0) {
          moves.push_back(createMove(solution.pathB[thirdIndex], solution.pathB[fourthIndex], solution.pathB[indexB], solution.pathB[(indexB + 1)%solution.pathB.size()], insideEdges, secondDelta));
        }
      }
   
    }
    return moves;
}
