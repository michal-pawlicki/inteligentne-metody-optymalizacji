#pragma once

#include <iostream>
#include <ctime>
#include "defs.hpp"

TSPSolution twoRegret(const TSPData& data, int startNode);

std::pair<int, int> findBestRegret(const TSPData& data, const std::vector<bool>& visited, std::vector<int> path );

int calculateDistanceRegret(const TSPData& data, const std::vector<int>& path);