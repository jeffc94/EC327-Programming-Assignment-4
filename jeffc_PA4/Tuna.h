#ifndef __Tuna__
#define __Tuna__

#include "Fish.h"
#include "Cave.h"

class Tuna : public Fish
{
public:
    Tuna();
    Tuna(int, Cave*,Model*);
    double get_speed();
    bool start_mating(Tuna*);
    bool update();
    void show_status();
    int timer;
    int mateTime;
    void do_mating();
    void save (ofstream& myfile);
private:
    bool initiator;
};

#endif /* defined(__Tuna__) */
