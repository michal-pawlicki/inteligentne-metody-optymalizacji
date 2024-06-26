#include <algorithm>
#include <random>
#include <iostream>
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

TSPSolution generateRandomSolution(const TSPData& data);

void printSolutionCycle(const TSPSolution& solution);

int findCityIndex(std::vector<int> path, int city);

Move createMove(int i, int j, int k, int l, moveType type, int delta);

int calculateDeltaInsideEdgesCache(const TSPData& data, const TSPSolution& solution, int i, int j, int k, int l, int pathIndex);

std::pair<int, int> edgeExistsAnywhere(const TSPSolution& solution, int i, int j);

int edgeExists(const TSPSolution& solution, int i, int j, int pathIndex);

int calculateDeltaOutsideCache(const TSPData& data, const TSPSolution& solution, int i, int firstPathIndex, int j, int secondPathIndex);

TSPSolution doInsideMoveEdgesCache(const TSPSolution& solution, int i, int j, int pathIndex);