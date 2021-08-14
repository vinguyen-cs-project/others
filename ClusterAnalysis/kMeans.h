/* Vi Nguyen CSCE2110.001
 * Project 2 Group 10 Part 2 and bonus
 * k-means header file
 * Version: 3.0
 * Date: Oct 29, 2019
 */
#ifndef KMEANS_H
#define KMEANS_H

#include "cluster.h"
#include "point.h"
#include <vector>
#include <iterator>
#include <list>
using namespace std;

list<Cluster>::iterator closeClus(const Point &x, list <Cluster> &clusters);
void kMeans(const vector<Point> &points, const vector<list<Cluster>> &kCentroids, int x);
void assignPoints(const vector <Point> &points, list <Cluster> &cluster);
Point closePoint(const Cluster &clus);
#endif
