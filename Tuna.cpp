#include <iostream>
#include <fstream>
#include "Tuna.h"
#include "GameObject.h"
#include "Cave.h"
#include "Model.h"

Tuna::Tuna() : Fish('T',10)
{
    this -> initiator = false;
}

Tuna::Tuna(int id, Cave* home, Model* m1) : Fish('T',10,home,id,m1)
{
    this -> initiator = false;
}

double Tuna::get_speed()
{
    return Fish::get_speed();
}

bool Tuna::update()
{
    if (state == 'h')
        //Check if there is a mate!
        for (std::list<Tuna*>::iterator it = (*world).tuna_points.begin(); it != (*world).tuna_points.end(); ++it)
        {
            start_mating(*it);
        }
    if (state == 'm')
    //Check all requirements for mating
    {
        if (timer == mateTime + 2)
        {
            if(initiator == true)
            {
                cout << "We made a new fish!" << endl;
                int temp = 0;
                int currentID;
                for (std::list<Tuna*>::iterator it = (*world).tuna_points.begin(); it != (*world).tuna_points.end(); ++it)
                {
                    currentID = (**it).get_id();
                    if (currentID > temp)
                        temp = currentID;
                }
                Tuna* babyTuna = new Tuna(currentID,home,world);
                (*world).add_new_tuna(babyTuna);
            }
            else
            {
                cout << "Luke I am not your father" << endl;
            }
            state = 'h';
        }
        else
        {
            cout << "Still mating..." << endl;
            timer++;
        }
    }
    else
        return Fish::update();
        return false;
}

void Tuna::show_status()
{
    Fish::show_status();
}

bool Tuna::start_mating(Tuna* tunaPtr)
{
    Cave* tunaHome = (*tunaPtr).home;
    CartPoint loca = (*home).get_location();
    CartPoint locb = (*tunaPtr).get_location();
    double caveSpace = (*tunaHome).get_space();
    double tunaSizeA = get_size();
    double tunaSizeB = (*tunaPtr).get_size();
    //See if you can mate
    if (state == 'h' && (*tunaPtr).state == 'h' && loca.x == locb.x && loca.y == locb.y && caveSpace >= 10
        && tunaSizeA >= 40 && tunaSizeA <= 60 && tunaSizeB >= 40 && tunaSizeB <= 60
        && caveSpace == (100 - (tunaSizeA + tunaSizeB)))
        {
            this -> initiator = true;
            do_mating();
            (*tunaPtr).do_mating();
            cout << "I found my mate!" << endl;
            mateTime = 0;
            timer = 0;
            return true;
        }
    else
        //cout << "Can't mate!" << endl;
        return false;
}

void Tuna::do_mating()
{
    this -> state = 'm';
}

void Tuna::save(ofstream& myfile)
{
    //Put member variables into arrays
    int reefID;
    double save_doubles[12];
    save_doubles[0] = get_id();
    save_doubles[1] = size;
    save_doubles[2] = prefeast_size;
    save_doubles[3] = energy;
    save_doubles[4] = location.x;
    save_doubles[5] = location.y;
    save_doubles[6] = delta.x;
    save_doubles[7] = delta.y;
    save_doubles[8] = destination.x;
    save_doubles[9] = destination.y;
    save_doubles[10] = (*home).get_id();
    if (reef==NULL)
        reefID = -1;
    else
        reefID = (*reef).get_id();
    save_doubles[11] = reefID;
    char save_chars[2];
    save_chars[0] = get_displaycode();
    save_chars[1] = state;
    //Read arrays into files
    for (int i = 0; i < 2; i++)
        myfile << save_chars[i] << " ";
    for (int i = 0; i < 12; i++)
        myfile << save_doubles[i] << " ";
}
