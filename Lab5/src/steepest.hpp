#include "defs.hpp"
#include "helpers.hpp"
#include <cmath>

TSPSolution steepestVertices(const TSPData& data, TSPSolution startingSolution);

TSPSolution steepestEdges(const TSPData& data, TSPSolution startingSolution);

std::pair<int, int> findBestOutsideMove(const TSPData& data, const TSPSolution& solution);

std::pair< int, std::pair<int, int> > findBestInsideMoveVertices(const TSPData& data, const TSPSolution& solution);

std::pair< int, std::pair<int, int> > findBestInsideMoveEdges(const TSPData& data, const TSPSolution& solution);