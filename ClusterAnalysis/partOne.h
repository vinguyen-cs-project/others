/*
 *******************************************************
  PROJECT 2 : CSCE 2110
  AUTHOR: Carlyn Thomsen
  GROUP MEMBERS: Reevs Cota, Kay Harris, Vi Nguyen
 *******************************************************

Reading in the configuration file,
configuring the system properly for the requested clustering,
reading in and storing the data points,
and providing requested output.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>

#include "point.h"
#include "cluster.h"

using namespace std;

class partOne
{
	private:
		int kmin, kmax;	//min and max number of clusters
		map<int, Point> pointsmap;
		vector<list<Cluster>> kclusters;	//maps from int to later be used to create the point
		vector<Point> points;	//vector of points
	public:
		partOne();	//constructor
		int getKMin();	//get function for min number of clusters
		int getKMax();	//get function for max number of clusters
		const map<int, Point> getPointsMap();
		const vector<list<Cluster>>& getKClusters();	//get function for map of points
		const vector<Point>& getPoints();	//get function for vector of points

};
