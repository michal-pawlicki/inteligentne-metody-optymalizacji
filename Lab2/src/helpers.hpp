#include <algorithm>
#include "defs.hpp"

std::vector<std::pair<int, int> > outsideMoves(const TSPSolution& solution);

std::vector<std::pair<int, int> > insideMoves(const std::vector<int>);

int calculateDeltaOutside(const TSPData& data, const TSPSolution& solution, int i, int j);

int calculateDeltaInsideVertices(const TSPData& data, const TSPSolution& solution, int i, int j, int pathIndex);

int calculateDeltaInsideEdges(const TSPData& data, const TSPSolution& solution, int i, int j, int pathIndex);

TSPSolution doOutsideMove(const TSPSolution& solution, int i, int j);

TSPSolution doInsideMoveVertices(const TSPSolution& solution, int i, int j, int pathIndex);

TSPSolution doInsideMoveEdges(const TSPSolution& solution, int i, int j, int pathIndex);

int calculateDistanceCycle(const TSPData& data, const std::vector<int>& cycle);