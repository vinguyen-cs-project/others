/************************************************
 * Kay Harris and Vi Nguyen
 * CSCE 2110.001 Project 2 Group 10
 * Cluster Header File
 ************************************************/

#ifndef cluster_h
#define cluster_h

#include <vector>

#include "point.h"

using namespace std;

class Cluster {
	private:
		int id;
		Point centroid;
		vector<Point> points;
	public:
		Cluster(int id, Point centroid);
		void pushCentroid();

		int getID() const;
		Point& getCentroid();
		const Point& getCentroid() const;
		vector<Point>& getPoints();
		const vector<Point>& getPoints() const;
		
		void updateCent();
		static double getCentDistance(const Cluster& a, const Cluster& b);
		static double getDistance(const Point& a, const Point& b);
		const bool operator == (const Cluster &c) const;
};

#endif
