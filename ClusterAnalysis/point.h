#ifndef point_h
#define point_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Point
{
	private:
		int id;	//ID of the point
		double xpos;	//x coordinate of the point
		double ypos;	//y coordinate of the point
	public:
		Point();
		Point(int ID, double X, double Y);	//constructor

		//get()/set() functions for the ID
		void setID(int ID);
		int getID() const;

		//get()/set() functions for the x coordinate
		void setX(double x);
		double getX() const;

		//get()/set() functions for the y coordinate
		void setY(double y);
		double getY() const;
		//overloading operator ==
		const bool operator == (const Point &x) const;
};

#endif
