#include "steepest.hpp"
#include "cycle_augmentation.hpp"

TSPSolution largeScaleNeighbourhoodSearch(const TSPData& data, bool doLocalSearch, int stopTime);

TSPSolution destroy(const TSPSolution& solution);

TSPSolution repair(const TSPData& data, const TSPSolution& solution);
