/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 2 Group 10
 * Linkage cpp File
************************************************/

#include <vector>
#include <list>
#include <set>

#include "linkage.h"
#include "point.h"
#include "cluster.h"
#include "dunn.h"

using namespace std;

// Constructor for the struct Line that fills everything in (except loc, because it has to be set after creation)
Linkage::Line::Line(list<Cluster>::iterator lower, list<Cluster>::iterator higher) : lower(lower), higher(higher), idsum(lower->getID() + higher->getID()) {
  dist = Cluster::getCentDistance(*lower, *higher);
}
// Update the distance after a centroid change
void Linkage::Line::recalculate() {
  dist = Cluster::getCentDistance(*lower, *higher);
}
// Used to help the ordered set order the Lines
const bool Linkage::Line::operator<(const Line& rhs) const {
  if (dist < rhs.dist) return true;
  else if (dist > rhs.dist) return false;
  else return idsum < rhs.idsum;
}

// Function that does all the centroid clustering
void Linkage::cluster(const vector<Point>& points) {
  // Starting with ID 1, create all Clusters using a Point
  list<Cluster> clusters;
  for (int i = 0; i < points.size(); i++) {
    Cluster cluster(i+1, points.at(i));
    cluster.pushCentroid();
    clusters.push_back(cluster);
  }

  // Pointers of Line are used because iterators change frequently
  // Sorter code to get the set to order the pointers
  auto cmp = [](Line* a, Line* b) { return *a < *b; };
  // A set sorting the distance of each Line between Clusters
  multiset<Line*, decltype(cmp)> ordered(cmp);
  // An array storing which Lines are connected to which Clusters (Cluster ID-1 matches position in array)
  set<Line*> connect[clusters.size()];

  // Fill ordered and connect
  for (auto it = clusters.begin(); it != clusters.end(); it++) {
    // Only iterate over Clusters after "it" (avoids duplicates while also telling later code which ID is lower)
    for (auto it2 = next(it); it2 != clusters.end(); it2++) {
      Line* line = new Line(it, it2);
      // Add Line to ordered and store its position (easier than looking for it later)
      line->loc = ordered.insert(line);
      // Write down that these Clusters have this Line
      connect[it->getID()-1].insert(line);
      connect[it2->getID()-1].insert(line);
    }
  }

  // So we know when to start performing Dunn's index
  const int half = clusters.size()/2;

  // Start counting heirarchy levels
  int level = 0; for (; clusters.size() > 1; level++) {
    // Print required output and potentially Dunn's index
    if (level % 10 == 0) {
      cout << "Hierarchy level " << level << " with " << clusters.size() << " clusters inside";
      if (clusters.size() < half) cout << " and a Dunn index of " << Dunn::dunn(clusters, 1);
      cout << endl;
    }

    // Grab the shortest Line from ordered and pull the iterators out for convenience
    Line* shortest = *ordered.begin();
    list<Cluster>::iterator keep = shortest->lower;
    list<Cluster>::iterator merge = shortest->higher;

    // Copy the Points of merge into keep, then recalculate centroid
    keep->getPoints().insert(keep->getPoints().begin(), merge->getPoints().begin(), merge->getPoints().end());
    keep->updateCent();

    // Remove all Lines containing merge from ordered and connections
    set<Line*>& cnctm = connect[merge->getID()-1];
    for (auto it = cnctm.begin(); it != cnctm.end(); it++) {
      Line* line = *it;
      // Erase this Line from ordered
      ordered.erase(line->loc);
      // Erase references to merge from the other Cluster's connections
      connect[(line->lower == merge ? line->higher : line->lower)->getID()-1].erase(line);
    }

    // No reason to keep merge's connections
    cnctm.clear();
    // Don't need merge anymore
    clusters.erase(merge);
    // Delete our shortest Line* (the previous loop removed all references to it)
    delete shortest;

    // Update all Lines connected to keep
    set<Line*>& cnctk = connect[keep->getID()-1];
    for (auto it = cnctk.begin(); it != cnctk.end(); it++) {
      Line* line = *it;
      // Since the Line's distance changes it needs to be removed and re-added
      ordered.erase(line->loc);
      line->recalculate();
      line->loc = ordered.insert(line);
    }
  }
  // Do the last cout after everything is done
  cout << "Hierarchy level " << level << " with 1 clusters inside" << endl;
}
