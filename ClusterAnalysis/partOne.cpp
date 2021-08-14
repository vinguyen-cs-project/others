#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#include "partOne.h"
#include "point.h"

using namespace std;

partOne::partOne()
{
	ifstream in;	//instream to read in the configuration file
	ifstream in2; //instream to read in the points file
	string current;	//variable to keep track of the word we are reading in

	// Read config file from user until a valid file is found
	while (true) {
		cout << "Enter configuration file name: ";
		cin >> current;
		in = ifstream(current);
		// Check if the config file exists
		if (in.is_open()) {
			// Read the first line to find the points file
			getline(in, current);
			in2 = ifstream(current.substr(6, current.length()));
			// Check if the points file exists
			if (in2.is_open()) break;
			else cout << "Cannot find points file" << endl;
		} else cout << "Cannot find config file" << endl;
	}

	//reads in next 2 lines of configuration file and assigns values to correct variables
	getline(in, current);
	kmin = stoi(current.substr(11, current.length()));
	getline(in, current);
	kmax = stoi(current.substr(11, current.length()));

	int id;	//ID of the point
	double xpos;	//x coordinate of point
	double ypos;	//y coordinate of point

	in2 >> id >> xpos >> ypos;	//reads in and assigns the first ID, X, and Y coordinate
	while(!in2.eof())	//continues while not the end of file
	{
		Point point(id, xpos, ypos);
		points.push_back(point);	//adds point to the vector of Point objects
		pointsmap.emplace(id, point); 	//adds point to the map of Point objects
		in2 >> id >> xpos >> ypos;
	}

	//reads in rest of configuration file
	list<Cluster> clusters;
	int kid, num;
	in >> current;
	while(!in.eof())	//continues to read in until it reaches the end of the file
	{
		num = stoi(current.substr(0, current.length()-1));  //accounts for the ":" after the number
		for (int i = 1; i <= num; i++)
		{
			in >> kid;
			clusters.push_back(Cluster(i, pointsmap.at(kid)));	//adds cluster to the vector
		}
		kclusters.push_back(clusters); // adds this vector of clusters to kclusters
		clusters.clear();
		in >> current;
	}
}

//get functions for all variables
int partOne::getKMin()
{
	return kmin;
}

int partOne::getKMax()
{
	return kmax;
}

const map<int, Point> partOne::getPointsMap()
{
	return pointsmap;
}

const vector<list<Cluster>>& partOne::getKClusters()
{
	return kclusters;
}

const vector<Point>& partOne::getPoints()
{
	return points;
}
