#include <stdlib.h>
#include <fstream>
#include "Shark.h"
#include "Fish.h"
#include "Model.h"
#include "Cave.h"
#include "CartPoint.h"

double gen_num(int in_int)
{
    srand(in_int);
    return rand()%20;
}


Shark::Shark() : Fish('S',20)
{
    attack_strength = 2;
    range = 1;
    target = NULL;
}

Shark::Shark(int in_id,Model* m1) : Fish('S',20,CartPoint(gen_num((*m1).get_time()),gen_num((*m1).get_time())),in_id,m1)
{
    attack_strength = 2;
    range = 1;
    target = NULL;
}

double Shark::get_speed()
{
    return Fish::get_speed();
}

void Shark::start_attack(Fish* target)
{
    CartPoint locA = (*target).get_location();
    CartPoint locB = location;
    double dist = cart_distance(locA,locB);
    if (dist <= 1)
    {
        cout << "Chomp!" << endl;
        this -> state = 'a';
        this -> target = target;
        (*target).get_bitten(attack_strength);
    }
    else
        cout << "Fish are friends, not food" << endl;
}

bool Shark::update()
{
    switch(state)
    {
    case 'x':
        return false;
    case 's':
        return false;
    case 'e':
        if (get_size() >= 2*get_prefeastsize())
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
    case 'a':
        CartPoint locA = (*target).get_location();
        CartPoint locB = location;
        double dist = cart_distance(locA,locB);
        if (dist > range)
        {
            cout << "Darn! It escaped!" << endl;
            state = 's';
            target = NULL;
        }
        else
        {
            char fishState = (*target).get_state();
            if (fishState == 'x')
            {
                cout << "I triumph!" << endl;
                state = 's';
                return true;
            }
            else
            {
                cout << "Chomp!" << endl;
                (*target).get_bitten(attack_strength);
                this -> energy = energy + 5;
                return false;
            }
        }
        return false;
    }
    return false;
}

void Shark::show_status()
{
    Fish::show_status();
}

void Shark::save(ofstream& myfile)
{
    int caveID,reefID,fishID;
    double save_doubles[15];
    save_doubles[0] = get_id();
    save_doubles[1] = size;
    save_doubles[2] = prefeast_size;
    save_doubles[3] = energy;
    save_doubles[4] = location.x;
    save_doubles[5] = location.y;
    save_doubles[6] = attack_strength;
    save_doubles[7] = range;
    save_doubles[8] = delta.x;
    save_doubles[9] = delta.y;
    save_doubles[10] = destination.x;
    save_doubles[11] = destination.y;
    if (home==NULL)
        caveID = -1;
    else
        caveID = (*home).get_id();
    save_doubles[12] = caveID;
    if (reef==NULL)
        reefID = -1;
    else
        reefID = (*reef).get_id();
    save_doubles[13] = reefID;
    if (target==NULL)
        fishID = -1;
    else
        fishID = (*target).get_id();
    save_doubles[14] = fishID;
    char save_chars[2];
    save_chars[0] = get_displaycode();
    save_chars[1] = state;
    for (int i = 0; i < 2; i++)
        myfile << save_chars[i] << " ";
    for (int i = 0; i < 15; i++)
        myfile << save_doubles[i] << " ";
}
