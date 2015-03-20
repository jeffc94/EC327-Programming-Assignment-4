#ifndef __Shark__
#define __Shark__

#include "Fish.h"

class Shark : public Fish
{
public:
    Shark();
    Shark(int,Model*);
    double get_speed();
    void start_attack(Fish* target);
    bool update();
    void show_status();
    void save(ofstream&);
private:
    int attack_strength;
    double range;
    Fish* target;
};

double gen_num(int);

#endif /* defined(__Shark__) */
