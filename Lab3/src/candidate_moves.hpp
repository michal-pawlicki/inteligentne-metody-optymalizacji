#include "defs.hpp"
#include "helpers.hpp"

TSPSolution candidatesEdges(const TSPData& data, const TSPSolution& solution, int k);

std::vector<std::pair<int, int> > candidateCityIndexes(const TSPData& data, int k);

std::pair<int, int> findCities(const TSPSolution& solution, int cityA, int cityB);

std::pair<int, int> areCitiesInSamePath(const TSPSolution& solution, int cityA, int cityB);
