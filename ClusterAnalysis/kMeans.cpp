/* Vi Nguyen CSCE2110.001
 * Project 2 Group 10 Part 2 and bonus
 * k-means clustering Cpp file
 * Version: 4.0
 * Date: Oct 29, 2019
 */

#include "kMeans.h"
#include <vector>
#include <cmath>
#include <list>
#include <iterator>
#include <algorithm>

#include "dunn.h"

//return an iterator to the closest cluster to point x
list<Cluster>::iterator closeClus(const Point &x, list<Cluster> &clusters) {
	list <Cluster>:: iterator i = clusters.begin();
	double min = clusters.front().getDistance(x, clusters.front().getCentroid());
	for (list<Cluster>::iterator it = clusters.begin()++; it !=clusters.end(); it++)
		if (it->getDistance(x, it->getCentroid()) < min) {
			min = it->getDistance(x, it->getCentroid());
			i = it;
		}
	return i;
}
//perform k-means/k-medoids clustering
void kMeans(const vector<Point> &points, const vector<list<Cluster>> &kCentroids, int x){ //x = 0 do k-means, otherwise do k-medoids
	list<Cluster> clusters;
	for (int i = 0; i < kCentroids.size(); i++) {
		//copy value of k and centroids that get stored in part One
		clusters = kCentroids[i];
		cout << "For a k value of " << kCentroids[i].size() << ", here is the information regarding its clusters:" << endl;
		//repeat assigning points to cluster and update centroid of cluster till there's no change
		list<Cluster> temp = clusters;
		while (true) {
			assignPoints(points, clusters);
			for (list<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++) {
				it->updateCent();
				if(x !=0) it->getCentroid() = closePoint(*it); //bonus
			}
			if (temp == clusters) break;
			else temp = clusters;
		}
		//print output
		for (list<Cluster>::iterator it = clusters.begin(); it != clusters.end(); it++) {
			cout << "Cluster " << it->getID() << " contains " << it->getPoints().size() << " points and the point ";
			if (x == 0) cout << closePoint(*it).getID() << " is closest to its centroid." << endl;
			else cout << it->getCentroid().getID() << " is its medoid." << endl;
		}
		cout << "The Dunn index for a k of " << clusters.size() << " is " << Dunn::dunn(clusters, x) << endl;
		clusters.clear();
	}
}
//assign points to all cluster
void assignPoints(const vector <Point> &points, list<Cluster> &clusters) {
	for (list<Cluster>::iterator it1 = clusters.begin(); it1 != clusters.end(); it1++)
		it1->getPoints().clear();
	for (int i = 0; i < points.size(); i++)
		closeClus(points[i],clusters)->getPoints().push_back(points[i]);
}
//find the closest point to centroid of cluster
Point closePoint(const Cluster &clus) {
	double min = clus.getDistance(clus.getCentroid(), clus.getPoints().at(0));
	Point x = clus.getPoints().at(0);
	for (int i = 1; i < clus.getPoints().size(); i++)
		if(clus.getDistance(clus.getCentroid(), clus.getPoints().at(i)) < min) {
			min = clus.getDistance(clus.getCentroid(), clus.getPoints().at(i));
			x = clus.getPoints().at(i);
		}
	return x;
}
