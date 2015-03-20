//
//  CoralReef.cpp
//  PA3_UnderTheSea
//

#include <iostream>
#include <fstream>
#include "CoralReef.h"
#include "GameObject.h"

//Default constructor
CoralReef::CoralReef() : GameObject('R',0)
{
    this -> state = 'f';
    this -> amount = 100;
    cout << "CoralReef default constructed" << endl;
}

//Other constructor
CoralReef::CoralReef(int in_id, CartPoint in_loc): GameObject('R', in_id, in_loc)
{
    this -> state = 'f';
    this -> amount = 100;
    cout << "CoralReef constructed" << endl;
}

//Destructor
CoralReef::~CoralReef()
{
    cout << "CoralReef destructed" << endl;
}

//Member functions
//Check if reef is empty
bool CoralReef::is_empty()
{
    if (amount == 0)
        return true;
    else
        return false;
}

//Provide food for fish
double CoralReef::provide_food(double amount_to_provide)
{
    if (amount >= amount_to_provide)
    {
        amount = amount - amount_to_provide;
        return amount_to_provide;
    }
    else
        return amount;
        amount = 0;
}

//Update CoralReef
bool CoralReef::update()
{
    if (is_empty() && state != 'e')
    {
        this -> state = 'e';
        this -> display_code = 'r';
        cout << "CoralReef " << get_id() << " has been depleted" << endl;
        return true;
    }
    else
        return false;
}

//Show status of CoralReef
void CoralReef::show_status()
{
    cout << "CoralReef status: " << display_code << " with ID " << get_id() << " at location " << location
    << " containing food " << amount << endl;
}

void CoralReef::save(ofstream& myfile)
{
    double save_doubles[4];
    save_doubles[0] = amount;
    save_doubles[1] = get_id();
    save_doubles[2] = location.x;
    save_doubles[3] = location.y;
    char save_chars[2];
    save_chars[0] = get_displaycode();
    save_chars[1] = get_state();
    for (int i = 0; i < 2; i++)
        myfile << save_chars[i] << " ";
    for (int i = 0; i < 4; i++)
        myfile << save_doubles[i] << " ";
}
