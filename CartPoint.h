//
//  CartPoint.h
//  PA3_UnderTheSea
//

#ifndef __CartPoint__
#define __CartPoint__

#include <iostream>
#include "CartVector.h"

class CartPoint
{
//Public member variables
public:
	double x;
	double y;
//Constructor
    CartPoint();
	CartPoint(double inputx, double inputy);
};

//Nonmember functions
double cart_distance(CartPoint p1, CartPoint p2);

//Nonmember overloaded operators
CartPoint operator+ (CartPoint p1, CartVector v1);

CartVector operator- (CartPoint p1, CartPoint p2);

ostream& operator<< (ostream &out, CartPoint &cPoint);

#endif /* defined(__CartPoint__) */
