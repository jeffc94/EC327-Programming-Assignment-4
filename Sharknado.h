#ifndef __Sharknado__
#define __Sharknado__

#include "Model.h"

class Sharknado
{
public:
    int timer;
    Sharknado();
    void sweep_away(Model&);
    void printout();
    int swept_nos[30];
    char swept_chars[30];
};

#endif //
