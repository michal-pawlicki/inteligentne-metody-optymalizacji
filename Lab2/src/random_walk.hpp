#include "defs.hpp"
#include "helpers.hpp"
#include <chrono>



TSPSolution randomWalkVertices(const TSPData& data, TSPSolution startingSolution, int timeLimit);

TSPSolution randomWalkEdges(const TSPData& data, TSPSolution startingSolution, int timeLimit);