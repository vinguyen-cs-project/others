#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "point.h"

using namespace std;

Point::Point()
{

}
//constructor
Point::Point(int ID, double X, double Y)
{
	id = ID;
	xpos = X;
	ypos = Y;
}

//get()/seet() functions for ID
void Point::setID(int ID)
{
	id = ID;
}
int Point::getID() const
{
	return id;
}

//get()/seet() functions for X coordinate
void Point::setX(double X)
{
	xpos = X;
}
double Point::getX() const
{
	return xpos;
}

//get()/seet() functions for Y coordinate
void Point::setY(double Y)
{
	ypos = Y;
}
double Point::getY() const
{
	return ypos;
}
//overloading operator ==
const bool Point::operator==(const Point &a) const {
	return id == a.getID() && xpos == a.getX() && ypos == a.getY(); 
}
