//
//  Model.cpp
//  PA3_UnderTheSea
//

#include <fstream>
#include "Model.h"
#include "Cave.h"
#include "Fish.h"
#include "GameObject.h"
#include "CoralReef.h"
#include "View.h"
#include "Tuna.h"
#include "Shark.h"

//Default constructor
Model::Model()
{
    time = 0;
    Cave* caveA = new Cave(1,CartPoint(5,1));
    Cave* caveB = new Cave(2,CartPoint(6,2));
    cave_points.push_front(caveA);
    cave_points.push_back(caveB);
    Tuna* tunaA = new Tuna(1,cave_points.front(),this);
    Tuna* tunaB = new Tuna(2,cave_points.back(),this);
    Tuna* tunaC = new Tuna(3,cave_points.back(),this);
    Shark* sharkA = new Shark(4,this);
    Shark* sharkB = new Shark(5,this);
    fish_points.push_front(tunaA);
    fish_points.push_back(tunaB);
    fish_points.push_back(tunaC);
    fish_points.push_back(sharkA);
    fish_points.push_back(sharkB);
    tuna_points.push_front(tunaA);
    tuna_points.push_back(tunaB);
    tuna_points.push_back(tunaC);
    CoralReef* reefA = new CoralReef(1,CartPoint(1,20));
    CoralReef* reefB = new CoralReef(2, CartPoint(20,1));
    CoralReef* reefC = new CoralReef(3, CartPoint(20,20));
    reef_points.push_front(reefA);
    reef_points.push_back(reefB);
    reef_points.push_back(reefC);
    obj_points.push_front(caveA);
    obj_points.push_back(caveB);
    obj_points.push_back(tunaA);
    obj_points.push_back(tunaB);
    obj_points.push_back(tunaC);
    obj_points.push_back(sharkA);
    obj_points.push_back(sharkB);
    obj_points.push_back(reefA);
    obj_points.push_back(reefB);
    obj_points.push_back(reefC);
    act_points = (obj_points);
    cout << "Model default constructed" << endl;
}

//Destructor
Model::~Model()
{
    obj_points.clear();
    cout << "Model destructed." << endl;
}

//Get Fish pointer
Fish* Model::get_Fish_ptr(int id_num)
{
    for (itFish = fish_points.begin(); itFish != fish_points.end(); ++itFish)
    {
        int idNum = (**itFish).get_id();
        if (idNum == id_num)
            return *itFish;
    }
    return NULL;
}

//Get Cave pointer
Cave* Model::get_Cave_ptr(int id_num)
{
    for (itCave = cave_points.begin(); itCave != cave_points.end(); ++itCave)
    {
        int idNum = (**itCave).get_id();
        if (idNum == id_num)
            return *itCave;
    }
    return NULL;
}

//Get CoralReef pointer
CoralReef* Model::get_CoralReef_ptr(int id_num)
{
    for (itReef = reef_points.begin(); itReef != reef_points.end(); ++itReef)
    {
        int idNum = (**itReef).get_id();
        if (idNum == id_num)
            return *itReef;
    }
    return NULL;
}

//Update model
bool Model::update()
{
    time++;
    for (itObj = act_points.begin(); itObj != act_points.end(); ++itObj)
    {
        if((**itObj).is_alive() == false)
            itObj = act_points.erase(itObj);
    }
    for (itObj = act_points.begin(); itObj != act_points.end(); ++itObj)
    {
        if((**itObj).update())
        {
            for (itObj++; itObj != act_points.end(); ++itObj)
            {
                (**itObj).update();
            }
            return true;
        }
    }
    return false;;
}

void Model::display(View& view)
{
    //Display time
    cout << "Time: " << time << endl;
    //Fill array with periods and spaces
    for (int i = 0; i < view_maxsize/2 + 1; i++)
    {
        for (int j = 0; j < view_maxsize/2 + 1; j++)
        {
            char * gridder = view.grid[i][j];
            *gridder = '.';
            *(gridder + 1) = ' ';
        }
    }
    //Plot the GameObjects
    for (itObj = act_points.begin(); itObj != act_points.end(); ++itObj)
    {
        view.plot(*itObj);
    }
    //Draw grid
    view.draw();
}

//Show status of model
void Model::show_status()
{
    for (std::list<GameObject*>::iterator it = obj_points.begin(); it != obj_points.end(); ++it)
        (**it).show_status();
}

int Model::get_time()
{
    return time;
}

void Model::add_new_tuna(Tuna* myTuna)
{
    //Add new tuna to all lists
    fish_points.push_back(myTuna);
    tuna_points.push_back(myTuna);
    obj_points.push_back(myTuna);
    act_points.push_back(myTuna);
}

void Model::add_new_shark(Shark* myShark)
{
    //Add new shark to all lists
    fish_points.push_back(myShark);
    obj_points.push_back(myShark);
    act_points.push_back(myShark);
}

void Model::add_new_cave(Cave* myCave)
{
    //Add new cave to all lists
    cave_points.push_back(myCave);
    obj_points.push_back(myCave);
    act_points.push_back(myCave);
}

void Model::add_new_reef(CoralReef* myReef)
{
    //Add new coral reef to all lists
    reef_points.push_back(myReef);
    obj_points.push_back(myReef);
    act_points.push_back(myReef);
}

void Model::save(ofstream& myfile)
{
    //Save time, then save display characters and IDs of all active objects
    myfile << time << " ";
    for (std::list<GameObject*>::iterator it = act_points.begin(); it != act_points.end(); ++it)
        myfile << (**it).get_displaycode() << (**it).get_id() << " ";
    myfile << "end" << endl;
}

void Model::restore(ifstream& myfile)
{
    myfile >> time;
}
