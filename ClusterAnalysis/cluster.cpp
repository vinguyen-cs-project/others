/************************************************
 * Kay Harris and Vi Nguyen
 * CSCE 2110.001 Project 2 Group 10
 * Cluster cpp File
 ************************************************/

#include <vector>
#include <cmath>
#include "cluster.h"
#include "point.h"

// Constructor to initialize the values
Cluster::Cluster(int id, Point centroid) : id(id), centroid(centroid) {}
// Removed from the constructor and made into its own function
void Cluster::pushCentroid() { points.push_back(centroid); }

// Getters
int Cluster::getID() const { return id; }
// References used in order to match getPoints()
Point& Cluster::getCentroid() { return centroid; }
const Point& Cluster::getCentroid() const { return centroid; }
// References used to avoid a bunch of vector copying
vector<Point>& Cluster::getPoints() { return points; }
const vector<Point>& Cluster::getPoints() const { return points; }

// Calculates the average and updates the centroid
void Cluster::updateCent() {
	double x = 0, y = 0;
	for (auto it = points.begin(); it != points.end(); it++) {
		x += it->getX(); y += it->getY();
	}
	centroid.setX(x/points.size());
	centroid.setY(y/points.size());
}
// Calculate Euclidean distance between centroids
double Cluster::getCentDistance(const Cluster& a, const Cluster& b) {
	return getDistance(a.centroid, b.centroid);
}
// Calculate Euclidean distance between Points
double Cluster::getDistance(const Point& a, const Point& b) {
	return sqrt((a.getX()-b.getX())*(a.getX()-b.getX())+(a.getY()-b.getY())*(a.getY()-b.getY()));
}
//overloading operator ==
const bool Cluster::operator==(const Cluster &c) const {
	return id == c.id && centroid == c.centroid && points == c.points;
}
