#pragma once

#include <iostream>
#include <ctime>
#include "defs.hpp"

TSPSolution cycleAugmentation(const TSPData& data, int startNode);

std::pair<int, int> findBestCycle(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path );

void printSolutionCycle(const TSPSolution& solution);

int calculateDistanceCycle(const TSPData& data, const std::vector<int>& path);