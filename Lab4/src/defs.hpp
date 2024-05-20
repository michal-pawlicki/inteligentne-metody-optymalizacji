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
  int distance;
};

enum moveType {
  outside,
  insideVertices,
  insideEdges,
  none
};

class Move {
  public:

    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    moveType type;
    int delta;

    bool operator==(const Move& other) const {
        return type == other.type &&
               i == other.i &&
               j == other.j &&
               k == other.k &&
               l == other.l &&
               delta == other.delta;
    }
};