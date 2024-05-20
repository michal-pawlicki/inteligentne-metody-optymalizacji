#include "steepest.hpp"

TSPSolution iteratedLocalSearch(const TSPData& data, int stopTime);

TSPSolution perturb(const TSPData& data, const TSPSolution& solution);