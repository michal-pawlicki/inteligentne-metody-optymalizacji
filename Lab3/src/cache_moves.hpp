#include "defs.hpp"
#include "helpers.hpp"

TSPSolution cacheEdges(const TSPData& data, const TSPSolution& solution);

std::vector<Move> generateMoves(const TSPData& data, const TSPSolution& solution);

bool compareMoves(const Move& move1, const Move& move2);

std::vector<Move> generateNewMoves(const TSPData& data, const TSPSolution& solution, Move move);