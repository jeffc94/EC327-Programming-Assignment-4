//
//  GameObject.cpp
//  PA3_UnderTheSea
//

#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "Model.h"

using namespace std;

//Default constructor
GameObject::GameObject(char in_code, int in_id)
{
    this -> display_code = in_code;
    this -> id_num = in_id;
    this -> location = CartPoint(0,0);
    cout << "GameObject default constructed" << endl;
}

//Other constructor
GameObject::GameObject(char in_code, int in_id, CartPoint in_loc)
{
    this -> display_code = in_code;
    this -> id_num = in_id;
    this -> location = CartPoint (in_loc);
    cout << "GameObject constructed" << endl;
}

GameObject::~GameObject()
{
    cout << "GameObject destructed" << endl;
}

//Member functions
//Get location of object
CartPoint GameObject::get_location()
{
    return location;
}

//Get ID number of object
int GameObject::get_id()
{
    return id_num;
}

//Update object (virtual)
bool GameObject::update()
{
    return true;
}

//Show status of object (virtual)
void GameObject::show_status()
{
    cout << display_code << " with ID " << id_num << " at location " << location << endl;
}

//Point to character and id number of Gameobject
void GameObject::drawself(char* grid)
{
    *grid = display_code;
    int objID = get_id();
    char idASC = objID;
    *(grid+1) = idASC;
}

char GameObject::get_state()
{
    return state;
}

bool GameObject::is_alive()
{
    return true;
}

void GameObject::set_location(int x, int y)
{
    location = CartPoint(x,y);
}

void GameObject::set_id(int id)
{
    id_num = id;
}

char GameObject::get_displaycode()
{
    return display_code;
}

void GameObject::save(ofstream& myfile)
{

}
