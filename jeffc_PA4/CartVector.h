//
//  CartVector.h
//  PA3_UnderTheSea
//

#ifndef __CartVector__
#define __CartVector__

#include <iostream>

using namespace std;

class CartVector
{
//Public member variables
public:
	double x;
	double y;
//Constructors
	CartVector();
	CartVector(double, double);
};

//Nonmember overloaded operators
CartVector operator* (CartVector v1, double d);

CartVector operator/ (CartVector v1, double d);

ostream& operator<< (ostream &out, CartVector &cVect);

#endif /* defined(__CartVector__) */
