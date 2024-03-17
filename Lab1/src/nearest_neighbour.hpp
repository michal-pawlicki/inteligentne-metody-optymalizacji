#pragma once

#include <iostream>
#include <ctime>
#include "defs.hpp"

TSPSolution nearestNeighbour(const TSPData& data, int startNode);

std::pair<int, int> findBest(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path );

void printSolution(const TSPSolution& solution);

int calculateDistance(const TSPData& data, const std::vector<int>& path);