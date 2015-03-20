//
//  CoralReef.h
//  PA3_UnderTheSea
//

#ifndef __CoralReef__
#define __CoralReef__

#include "GameObject.h"

class Model;

class CoralReef : public GameObject
{
public:
//Public member functions
    bool is_empty();
    double provide_food(double amount_to_provide = 20.0);
    bool update();
    void show_status();
    void save(ofstream&);
//Constructors
    CoralReef();
    CoralReef(int, CartPoint);
//Destructor
    ~CoralReef();
private:
//Private member variables
    double amount;
};

#endif /* defined(__CoralReef__) */
