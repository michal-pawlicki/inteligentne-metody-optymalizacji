#include "defs.hpp"
#include "helpers.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>

TSPSolution greedyVertices(const TSPData& data, TSPSolution startingSolution);

TSPSolution greedyEdges(const TSPData& data, TSPSolution startingSolution);

std::pair<int, int> findFirstOutsideMove(const TSPData& data, const TSPSolution& solution);

std::pair< int, std::pair<int, int> > findFirstInsideMoveVertices(const TSPData& data, const TSPSolution& solution);

std::pair< int, std::pair<int, int> > findFirstInsideMoveEdges(const TSPData& data, const TSPSolution& solution);