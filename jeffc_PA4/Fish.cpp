//
//  Fish.cpp
//  PA3_UnderTheSea
//

#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "Fish.h"
#include "CoralReef.h"
#include "Cave.h"
#include "Model.h"
#include "Tuna.h"

//Default constructor
Fish::Fish(char dispCode, int fishSize) : GameObject(dispCode,0)
{
    this -> state = 'h';
    this -> energy = 15;
    this -> size = fishSize;
    this -> prefeast_size = fishSize;
    this -> reef = NULL;
    this -> home = NULL;
    cout << "Fish default constructed" << endl;
}

//Other constructors
Fish::Fish(char dispCode, int fishSize, Cave* home, int in_id, Model* m1) : GameObject (dispCode, in_id, (*home).get_location())
{
    this -> world = m1;
    this -> energy = 15;
    this -> size = fishSize;
    this -> prefeast_size = fishSize;
    this -> reef = NULL;
    this -> home = home;
    (*home).hide_fish(this);
    this -> state = 'h';
    cout << "Fish constructed" << endl;
}

Fish::Fish(char dispCode, int fishSize, CartPoint loc, int in_id, Model* m1) : GameObject (dispCode, in_id, loc)
{
    this -> world = m1;
    this -> energy = 15;
    this -> size = fishSize;
    this -> prefeast_size = fishSize;
    this -> reef = NULL;
    this -> home = NULL;
    this -> state = 'f';
    cout << "Fish constructed" << endl;
}

//Destructor
Fish::~Fish()
{
    cout << "Fish destructed" << endl;
}

//Get size of fish
double Fish::get_size()
{
    return size;
}

double Fish::get_prefeastsize()
{
    return prefeast_size;
}

//Get speed of fish
//Pure virtual function
double Fish::get_speed()
{
    if (display_code == 'T')
        return (1/size)*(energy)*4;
    else
        return (1/size)*(energy)*8;
}

//Check if fish is hidden
bool Fish::is_hidden()
{
    if (state == 'h')
        return true;
    else
        return false;
}

//Set up destination
void Fish::setup_destination(CartPoint dest)
{
    this -> destination = dest;
    double fishSpeed = get_speed();
    this -> delta = (destination - location) * (fishSpeed/cart_distance(destination,location));
}

//Float in place
void Fish::float_in_place()
{
    //Release fish if hidden
    if (is_hidden())
        (*home).release_fish(this);
    this -> state = 'f';
    cout << "Stopping " << get_id() << endl;
    cout << display_code << get_id() << ": Resting my fins" << endl;
}

//Start swimming to destination
void Fish::start_swimming(CartPoint dest)
{
    //Release fish if hidden
    if (is_hidden())
        (*home).release_fish(this);
    setup_destination(dest);
    this -> state = 's';
    cout << "Swimming " << get_id() << " to " << dest << endl;
    cout << display_code << get_id() << ": On my way" << endl;
}

//Start eating at reef
void Fish::start_eating(CoralReef* destReef)
{
    //Release fish if hidden
    if (is_hidden())
        (*home).release_fish(this);
    this -> reef = destReef;
    setup_destination((*destReef).get_location());
    this -> prefeast_size = size;
    this -> state = 'o';
    cout << "Fish " << get_id() << " eating at CoralReef " << (*destReef).get_id()
    << " and returning back to Cave " << (*home).get_id() << endl;
    cout << display_code << get_id() << ": Food here I come!" << endl;
}

//Start hiding at cave
void Fish::start_hiding(Cave* destCave)
{
    //Release fish if hidden
    if (is_hidden())
        (*home).release_fish(this);
    setup_destination((*destCave).get_location());
    this -> home = destCave;
    this -> state = 'z';
    cout << "Fish " << get_id() << " swimming to Cave " << (*home).get_id() << endl;
    cout << display_code << get_id() << ": Off to safety" << endl;
}

//Update location of fish
bool Fish::update_location()
{
    if (fabs(destination.x - location.x) <= fabs(delta.x) && fabs(destination.y - location.y) <= fabs(delta.y))
    {
        cout << display_code << get_id() << ": I'm there!" << endl;
        this -> location = destination;
        return true;
    }
    else
        location = location + delta;
        cout << display_code << get_id() << ": just keep swimming..." << endl;
        return false;
}

//Update fish
//Virtual function
bool Fish::update()
{
    switch (state)
    {
        case 'f':
            return false;
            break;
        case 's':
            //Return true when fish reaches destination
            if (update_location())
            {
                state = 'f';
                return true;
            }
            else
            {
                state = 's';
                return false;
            }
            break;
        case 'o':
            //Return true when fish reaches destination and change state to eating
            if (update_location())
            {
                state = 'e';
                cout << display_code << get_id() << ": Starting to dine at a coral reef" << endl;
                return true;
            }
            else
            {
                state = 'o';
                return false;
            }
            break;
        case 'e':
            //If fish has eaten enough, return true and change state to zooming home
            if (size >= 2*prefeast_size)
            {
                setup_destination((*home).get_location());
                cout << display_code << get_id() << ": I'm full. I'm heading home" << endl;
                state = 'z';
                return true;
            }
            else
            {
                //If reef is empty, change state to floating
                if ((*reef).is_empty())
                {
                    cout << display_code << get_id() << ": This reef has no more food for me..." << endl;
                    this -> state = 'f';
                }
                else
                //Allow fish to eat
                {
                    double foodAmount = (*reef).provide_food();
                    size = (foodAmount)/2 + size;
                    cout << display_code << get_id() << ": Grew to size " << size << endl;
                }
                return false;
            }
            break;
        case 'z':
            //Return true if fish reaches home
            if (update_location())
            {
                //If there is enough room in cave, change state of fish to hidden
                if ((*home).hide_fish(this))
                {
                    state = 'h';
                    cout << display_code << get_id() << ": I am hidden and safe" << endl;
                }
                //If there is no space in cave, change state of fish to panicked
                else
                {
                    state = 'p';
                    cout << display_code << get_id() << ": Help! My home is full" << endl;
                }
                return true;
            }
            else
                return false;
            break;
        case 'h':
            if (is_hidden())
            {
                energy = energy - energy/4;
                if (energy <= 5)
                    state = 'x';
                return false;
            }
            break;
        case 'p':
            return false;
            break;
        case 'x':
            return false;
            break;
    }
    return false;
}

//Show status of fish
void Fish::show_status()
{
    switch (state)
    {
        case 'f':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " is floating. Has a size of: " << get_size() << " and energy of: " << energy << endl;
            break;
        case 's':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " has a speed of: " << get_speed() << " and is heading to: " << destination << endl;
            break;
        case 'o':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " is outbound to Reef: " << (*reef).get_id() << " with a speed of " << get_speed() << endl;
            break;
        case 'e':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " is eating at Reef " << (*reef).get_id() << endl;
            break;
        case 'z':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " is swimming to cave " << (*home).get_id() << " with a speed of " << get_speed() << endl;
            break;
        case 'h':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " is hidden in Cave " << (*home).get_id() << endl;
            break;
        case 'p':
            cout << "Fish status: " << display_code << " with ID " << get_id() << " at location " << location
            << " is panicked!!! And has a size of " << size << endl;
            break;
    }
}

void Fish::start_attack(Fish* fishPtr)
{
    cout << "I cannot attack" << endl;
}

void Fish::start_mating(Fish* fishPtr)
{
    cout << "I cannot mate" << endl;
}

void Fish::get_bitten(int attack_strength)
{
    energy = energy - attack_strength;
    if (energy <= 0)
    {
        cout << "Oh no, I've become chum!" << endl;
        this -> state = 'x';
    }
    else
        cout << "Ouch!" << endl;
}

bool Fish::is_alive()
{
    if (state == 'x')
        return false;
    else
        return true;
}

void Fish::save(ofstream& myfile)
{

}
