//
//  GameObject.h
//  PA3_UnderTheSea
//

#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include <iostream>
#include "CartPoint.h"

class GameObject
{
public:
//Public member functions
    CartPoint get_location();
    int get_id();
    virtual void show_status();
    virtual bool update();
    void drawself(char* grid);
    char get_state();
    virtual bool is_alive();
    void set_location(int,int);
    void set_id(int);
    char get_displaycode();
    virtual void save(ofstream&);
//Constructors
    GameObject(char, int);
    GameObject(char, int, CartPoint);
//Destructor
    virtual ~GameObject();
protected:
//Protected member variables
    char display_code;
    char state;
    CartPoint location;
private:
//Private member variables
    int id_num;
};

#endif /* defined(__CartVector__) */
