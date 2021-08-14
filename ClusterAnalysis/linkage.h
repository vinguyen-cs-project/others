/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 2 Group 10
 * Linkage Header File
************************************************/

#ifndef linkage_h
#define linkage_h

#include <vector>
#include <list>
#include <set>
#include <map>

#include "point.h"
#include "cluster.h"

using namespace std;

class Linkage {
  private:
    struct Line {
      const list<Cluster>::iterator lower, higher;
      const int idsum;
      double dist;
      multiset<Line*>::iterator loc;

      Line(list<Cluster>::iterator lower, list<Cluster>::iterator higher);
      void recalculate();
      const bool operator<(const Line& rhs) const;
    };
  public:
    static void cluster(const vector<Point>& points);
};

#endif
