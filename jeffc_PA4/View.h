//
//  View.h
//  PA3_UnderTheSea
//

#ifndef __View__
#define __View__

#include "CartPoint.h"
#include "GameObject.h"

const int view_maxsize = 20;

class View
{
public:
    View();
    void clear();
    void plot(GameObject* ptr);
    void draw();
    char grid[view_maxsize][view_maxsize][2];
private:
    int size;
    double scale;
    CartPoint origin;
    bool get_subscripts(int &ix, int &iy, CartPoint location);
};

#endif /* defined(__View__) */
