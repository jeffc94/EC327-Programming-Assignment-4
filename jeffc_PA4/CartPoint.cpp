//
//  CartPoint.cpp
//  PA3_UnderTheSea
//

#include <cmath>
#include "CartPoint.h"
#include "CartVector.h"

//Default constructor
CartPoint::CartPoint()
{
    this -> x = 0;
    this -> y = 0;
}

//Other constructor
CartPoint::CartPoint(double inputx, double inputy)
{
	this -> x = inputx;
	this -> y = inputy;
}

//Distance function
double cart_distance(CartPoint p1, CartPoint p2)
{
    double xDiff = p1.x - p2.x;
    double yDiff = p1.y - p2.y;
    double xSqu = xDiff * xDiff;
    double ySqu = yDiff * yDiff;
    return sqrt(xSqu + ySqu);
}

//Overloaded addition operator
CartPoint operator+ (CartPoint p1, CartVector v1)
{
    CartPoint myPoint(0,0);
    myPoint.x = p1.x + v1.x;
    myPoint.y = p1.y + v1.y;
    return myPoint;
}

//Overloaded subtraction operator
CartVector operator- (CartPoint p1, CartPoint p2)
{
    CartVector myVect;
    myVect.x = p1.x - p2.x;
    myVect.y = p1.y - p2.y;
    return myVect;
}

//Overloaded output operator
ostream& operator<< (ostream &out, CartPoint &cPoint)
{
    out << "(" << cPoint.x << ", " << cPoint.y << ")";
    return out;
}
