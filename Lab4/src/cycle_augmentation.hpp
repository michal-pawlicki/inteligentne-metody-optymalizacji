#pragma once

#include <iostream>
#include <ctime>
#include "defs.hpp"
#include "helpers.hpp"

TSPSolution cycleAugmentation(const TSPData& data, int startNode);

TSPSolution cycleAugmentation(const TSPData& data, const TSPSolution& solution);

std::pair<int, int> findBestCycle(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path );
