//
//  GameCommand.cpp
//  PA3_UnderTheSea
//

#include <exception>
#include <iostream>
#include <fstream>
#include "GameCommand.h"
#include "GameObject.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "Cave.h"
#include "Model.h"
#include "Fish.h"
#include "CoralReef.h"
#include "InputHandling.h"
#include "Shark.h"
#include "Tuna.h"

using namespace std;

void do_swim_command(Model& model)
{
    int fishID, xcoor, ycoor;
    if (!(cin >> fishID))
        throw InvalidInput("Was expecting an integer");
    if (!(cin >> xcoor >> ycoor))
        throw InvalidInput("Was expecting an integer");
    //Get pointer to corresponding Fish ID
    Fish* fishPtr = model.get_Fish_ptr(fishID);
    if (fishPtr==(Fish*)NULL)
        throw InvalidInput("Invalid fish ID");
    CartPoint destcoor = CartPoint(xcoor,ycoor);
    //Run swim function to input CartPoint
    (*fishPtr).start_swimming(destcoor);
}

void do_eat_command(Model& model)
{
    int fishID, reefID;
    if(!(cin >> fishID))
        throw InvalidInput("Was expecting an integer");
    if(!(cin >> reefID))
        throw InvalidInput("Was expecting an integer");
    //Get pointer to corresponding Fish ID
    Fish* fishPtr = model.get_Fish_ptr(fishID);
    if (fishPtr==(Fish*)NULL)
        throw InvalidInput("Invalid fish ID");
    //Get pointer to corresponding Reef ID
    CoralReef* reefPtr = model.get_CoralReef_ptr(reefID);
    if (reefPtr==(CoralReef*)NULL)
        throw InvalidInput("Invalid reef ID");
    //Run eat function to input CoralReef
    (*fishPtr).start_eating(reefPtr);
}

void do_float_command(Model& model)
{
    int fishID;
    if (!(cin >> fishID))
        throw InvalidInput("Was expecting an integer");
    //Get pointer to corresponding Fish ID
    Fish* fishPtr = model.get_Fish_ptr(fishID);
    if (fishPtr==(Fish*)NULL)
        throw InvalidInput("Invalid fish ID");
    //Run float function for Fish
    (*fishPtr).float_in_place();
}

void do_zoom_command(Model& model)
{
    int fishID, caveID;
    if (!(cin >> fishID))
        throw InvalidInput("Was expecting an integer");
    if (!(cin >> caveID))
        throw InvalidInput("Was expecting an integer");
    //Get pointer to corresponding Fish ID
    Fish* fishPtr = model.get_Fish_ptr(fishID);
    if (fishPtr==(Fish*)NULL)
        throw InvalidInput("Invalid fish ID");
    //Get pointer to corresponding Cave ID
    Cave* cavePtr = model.get_Cave_ptr(caveID);
    if (cavePtr==(Cave*)NULL)
        throw InvalidInput("Invalid cave ID");
    //Run hide function to input Cave
    (*fishPtr).start_hiding(cavePtr);
}

void do_go_command(Model& model)
{
    //Advance one time tick in the game
    cout << "Advancing one tick" << endl;
    model.update();
    model.show_status();
}

void do_run_command(Model& model)
{
    //Advance until something happens (until update returns true or 5 ticks pass)
    cout << "Advancing to next event" << endl;
    for (int i = 0; i < 5; i++)
    {
        if (model.update())
        {
            break;
        }
        else
            continue;
    }
    model.show_status();
}

void do_attack_command(Model& model)
{
    int fishoneID, fishtwoID;
    if (!(cin >> fishoneID))
        throw InvalidInput("Was expecting an integer");
    if (!(cin >> fishtwoID))
        throw InvalidInput("Was expecting an integer");
    //Get corresponding fish pointer
    Fish* fishonePtr = model.get_Fish_ptr(fishoneID);
    if (fishonePtr==(Fish*)NULL)
        throw InvalidInput("Invalid fish ID");
    //Get corresponding fish pointer
    Fish* fishtwoPtr = model.get_Fish_ptr(fishtwoID);
    if (fishtwoPtr==(Fish*)NULL)
        throw InvalidInput("Invalid fish ID");
    //Call attack function
    (*fishonePtr).start_attack(fishtwoPtr);
}

void do_new_command(Model& model)
{
    Model* modelPtr = &model;
    char type;
    int id_numA, id_numB, xcoor, ycoor;
    cin >> type;
    if (type != 'R' && type != 'C' && type != 'S' && type!= 'T')
        throw InvalidInput("Invalid type");
    if (!(cin >> id_numA))
        throw InvalidInput("Was expecting an integer");
    //Make a new shark
    if (type == 'S')
    {
        Fish* fishPtr = model.get_Fish_ptr(id_numA);
        if (fishPtr!=(Fish*)NULL)
            throw InvalidInput ("ID already taken!");
        else
        {
            Shark* myShark = new Shark(id_numA,modelPtr);
            model.add_new_shark(myShark);
        }
    }
    //Make a new tuna
    else if (type == 'T')
    {
        if(!(cin >> id_numB))
            throw InvalidInput("Was expecting an integer");
        Fish* fishPtr = model.get_Fish_ptr(id_numA);
        if (fishPtr!=(Fish*)NULL)
            throw InvalidInput("ID already taken!");
        Cave* cavePtr = model.get_Cave_ptr(id_numB);
        if (cavePtr==(Cave*)NULL)
            throw InvalidInput("Cave ID invalid!");
        Tuna* myTuna = new Tuna(id_numA,cavePtr,modelPtr);
        model.add_new_tuna(myTuna);
    }
    //Make a new cave
    else if (type == 'C')
    {
        if (!(cin >> xcoor >> ycoor))
            throw InvalidInput("Was expecting an integer");
        Cave* cavePtr = model.get_Cave_ptr(id_numA);
        if (cavePtr!=(Cave*)NULL)
            throw InvalidInput("ID already taken!");
        else
        {
            Cave* myCave = new Cave(id_numA,CartPoint(xcoor,ycoor));
            model.add_new_cave(myCave);
        }
    }
    //Make a new CoralReef
    else
    {
        if (!(cin >> xcoor >> ycoor))
            throw InvalidInput("Was expecting an integer");
        CoralReef* reefPtr = model.get_CoralReef_ptr(id_numA);
        if(reefPtr!=(CoralReef*)NULL)
            throw InvalidInput ("ID already taken!");
        else
        {
            CoralReef* myReef = new CoralReef(id_numA, CartPoint(xcoor,ycoor));
            model.add_new_reef(myReef);
        }
    }
}

void do_save_command(Model& model)
{
    //Input file name
    string filename;
    cin >> filename;
    const char* filer = filename.c_str();
    //cout << filer;
    ofstream myfile;
    myfile.open(filer);
    //Call save functions
    model.save(myfile);
    for (std::list<GameObject*>::iterator it = model.obj_points.begin(); it != model.obj_points.end(); ++it)
    {
        (**it).save(myfile);
        myfile << "\n";
    }
    myfile.close();
}

void do_restore_command(Model& model)
{
    string filename;
    cin >> filename;
    const char* filer = filename.c_str();
    ifstream myfile(filer);
    if (myfile.is_open())
    {
        model.restore(myfile);
    }
}
