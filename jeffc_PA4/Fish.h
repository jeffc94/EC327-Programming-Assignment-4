//
//  Fish.h
//  PA3_UnderTheSea
//

#ifndef __Fish__
#define __Fish__

#include "GameObject.h"
#include "CoralReef.h"

class Model;
class Cave;
class Fish : public GameObject
{
public:
//Constructors
    Fish(char,int);
    Fish(char,int,Cave*,int,Model*);
    Fish(char,int,CartPoint,int,Model*);
//Destructor
    ~Fish();
//Public member functions
    double get_size();
    double get_prefeastsize();
    virtual double get_speed() = 0;
    bool is_hidden();
    void float_in_place();
    void start_swimming(CartPoint);
    void start_eating(CoralReef*);
    void start_hiding(Cave*);
    virtual bool update();
    void show_status();
    virtual void start_attack(Fish*);
    virtual void start_mating(Fish*);
    void get_bitten(int);
    bool is_alive();
    virtual void save(ofstream&);
protected:
    Cave* home;
    Model* world;
    void setup_destination(CartPoint);
    bool update_location();
    double energy;
    double size;
    double prefeast_size;
    CartPoint destination;
    CartVector delta;
    CoralReef* reef;
};

#endif /* defined(__Fish__) */
