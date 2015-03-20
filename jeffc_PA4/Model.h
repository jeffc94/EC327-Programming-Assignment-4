//
//  Model.h
//  PA3_UnderTheSea
//

#ifndef __Model__
#define __Model__

#include <list>
#include "Fish.h"
#include "View.h"
#include "GameObject.h"
#include "Tuna.h"
#include "Shark.h"

using namespace std;

class Model
{
public:
//Public member functions
    Fish* get_Fish_ptr(int id_num);
    CoralReef* get_CoralReef_ptr(int id_num);
    Cave* get_Cave_ptr(int id_num);
    bool update();
    void display(View& view);
    void show_status();
    int get_time();
    std::list<GameObject*>::iterator itObj;
    std::list<Fish*>::iterator itFish;
    std::list<Cave*>::iterator itCave;
    std::list<CoralReef*>::iterator itReef;
    std::list<Tuna*> tuna_points;
    std::list<Fish*> fish_points;
    std::list<GameObject*> obj_points;
    std::list<Cave*> cave_points;
    std::list<CoralReef*> reef_points;
    std::list<GameObject*> act_points;
    void add_new_tuna(Tuna*);
    void add_new_shark(Shark*);
    void add_new_cave(Cave*);
    void add_new_reef(CoralReef*);
    void save(ofstream&);
    void restore(ifstream&);
//Constructor
    Model();
//Destructor
    ~Model();
private:
//Private member variables
    int time;
};

#endif /* defined(__Model__) */
