/************************************************
 * Kay Harris
 * kayharris2@my.unt.edu
 * CSCE 2110.001 Project 2 Group 10
 * Dunn cpp File
************************************************/

#include <iostream>
#include <list>
#include <limits>

#include "dunn.h"
#include "point.h"
#include "cluster.h"

using namespace std;

int Dunn::kvals[3] = {};
double Dunn::dunns[3] = {};

// Calculates the Dunn index for a list of Clusters
double Dunn::dunn(const list<Cluster>& clusters, int type) {
  // type: 0 for k-means, 1 for centroid-linkage, and 2 for k-medoid
  // Using this makes the code reusable and provides an easy way to store and manage data for each type of clustering

  // Set max (inter-cluster distance) to a low number and min (intra-cluster distance) to a high number
  // This way they will immediately be replaced with actual values without needing extra logic
  double max = std::numeric_limits<double>::min();
  double min = std::numeric_limits<double>::max();

  // Go through each cluster
  for (auto c1 = clusters.begin(); c1 != clusters.end(); c1++) {
    auto points1 = c1->getPoints();
    // Ignore clusters that contain only a single point
    if (points1.size() <= 1) continue;
    // Try to find a bigger inter-cluster distance by comparing all points in this cluster
    for (auto p1 = points1.begin(); p1 != points1.end(); p1++) {
      for (auto p2 = next(p1); p2 != points1.end(); p2++) {
        // Where p1 and p2 are in the same cluster (c1)
        double d = Cluster::getDistance(*p1, *p2);
        if (d > max) max = d;
      }
    }

    // Try to find a smaller intra-cluster distance by comparing all the points in this cluster to all the points in all other clusters
    for (auto c2 = next(c1); c2 != clusters.end(); c2++) {
      auto points2 = c2->getPoints();
      // Ignore clusters that contain only a single point
      if (points2.size() <= 1) continue;
      for (auto p1 = points1.begin(); p1 != points1.end(); p1++) {
        for (auto p2 = points2.begin(); p2 != points2.end(); p2++) {
          // Where p1 is in c1 and p2 is in c2
          double d = Cluster::getDistance(*p1, *p2);
          if (d < min) min = d;
        }
      }
    }
  }

  // Now that we've compared all the values, we can calculate the Dunn index based on what we found
  double dunn = min/max;
  // Lastly, see if this index is bigger that previous runs, and if so, store it for the analysis step
  if (dunns[type] < dunn) {
    kvals[type] = clusters.size();
    dunns[type] = dunn;
  }

  return dunn;
}

void Dunn::printAnalysis() {
  // This code really just prints out the stuff we saved earlier
  cout << "For k-means, a k value of " << kvals[0] << " had the highest Dunn index of " << dunns[0] << endl;
  cout << "For centroid-linkage clustering, " << kvals[1] << " clusters had the highest Dunn index of " << dunns[1] << endl;
  cout << "For k-medoid, a k value of " << kvals[2] << " had the highest Dunn index of " << dunns[2] << endl;
}
