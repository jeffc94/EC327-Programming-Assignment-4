//
//  CartVector.cpp
//  PA3_UnderTheSea
//

#include "CartVector.h"

//Default constructor
CartVector::CartVector()
{
	this -> x = 0.0;
	this -> y = 0.0;
}

//Other constructor
CartVector::CartVector(double x, double y)
{
	this -> x = x;
	this -> y = y;
}

//Overloaded multiplication operator
CartVector operator* (CartVector v1, double d)
{
  CartVector myVect;
  myVect.x = v1.x * d;
  myVect.y = v1.y * d;
  return myVect;
}

//Overloaded division operator
CartVector operator/ (CartVector v1, double d)
{
  CartVector myVect;
  myVect.x = v1.x / d;
  myVect.y = v1.y / d;
  return myVect;
}

//Overloaded output operator
ostream& operator<< (ostream &out, CartVector &cVect)
{
  out << "<" << cVect.x << ", " << cVect.y << ">";
  return out;
}
