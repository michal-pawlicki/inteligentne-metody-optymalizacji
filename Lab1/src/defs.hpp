#pragma once


#include <vector>


struct Point {
  int x;
  int y;
};

struct TSPData {
  std::vector<std::vector<int> > distances;
  std::vector<Point> coordinates;
};

struct TSPSolution {
  std::vector<int> pathA;
  std::vector<int> pathB;
};
