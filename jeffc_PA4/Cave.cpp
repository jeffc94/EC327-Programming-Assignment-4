//
//  Cave.cpp
//  PA3_UnderTheSea
//

#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "Cave.h"
#include "Fish.h"
#include "Model.h"

//Default constructor
Cave::Cave() : GameObject('c',0)
{
    this -> state = 'e';
    this -> space = 100;
    cout << "Cave default constructed" << endl;
}

//Other constructor
Cave::Cave(int in_id, CartPoint in_loc) : GameObject ('c',in_id,in_loc)
{
    this -> state = 'e';
    this -> space = 100;
    cout << "Cave constructed" << endl;
}

//Destructor
Cave::~Cave()
{
    cout << "Cave destructed" << endl;
}

//Member functions
//Hide fish
bool Cave::hide_fish(Fish* fish_to_hide)
{
    double fishSize = (*fish_to_hide).get_size();
    if (space >= fishSize && !((*fish_to_hide).is_hidden()))
    {
        space = space - fishSize;
        return true;
    }
    else
        return false;
}

//Release fish
bool Cave::release_fish(Fish* fish_to_release)
{
    double fishSize = (*fish_to_release).get_size();
    if ((*fish_to_release).is_hidden())
    {
        space = space + fishSize;
        return true;
    }
    else
        return false;
}

//Update cave
bool Cave::update()
{
    if (space == 0 && state != 'p')
    {
        this -> state = 'p';
        this -> display_code = 'C';
        cout << "Cave " << get_id() << " is packed like sardines" << endl;
        return true;
    }
    else if (space != 0 && state == 'p')
    {
        this -> state = 'e';
        this -> display_code = 'c';
        return true;
    }
    else
        return false;
}

//Show status of cave
void Cave::show_status()
{
    cout << "Cave status: " << display_code << " with ID " << get_id() << " at location " << location
    << " has a space of " << space << endl;
}

double Cave::get_space()
{
    return space;
}

void Cave::save(ofstream& myfile)
{
    double save_doubles[4];
    save_doubles[0] = space;
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


