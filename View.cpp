//
//  View.cpp
//  PA3_UnderTheSea
//

#include "View.h"

//Default constructor
View::View()
{
    this -> size = 11;
    this -> scale = 2;
    this -> origin = CartPoint(0,0);
}

//Gets Cartesian point subscripts of a location according to scale
bool View::get_subscripts(int& ix, int& iy, CartPoint location)
{
    CartVector gridLoc = (location - origin)/scale;
    ix = gridLoc.x;
    iy = gridLoc.y;
    if (ix >= 0 && ix <= 10 && iy >= 0 && iy <= 10)
        return true;
    else
    {
        cout << "An object is outside the display" << endl;
        return false;
    }
}

//Plots GameObject locations
void View::plot(GameObject* ptr)
{
    int ix, iy;
    if (get_subscripts(ix, iy, (*ptr).get_location()))
    {
        //If current location is empty, point to character and ID
        if (grid[10-iy][ix][0] == '.')
            (*ptr).drawself(grid[10-iy][ix]);
        //If current location is already filled, point to asterisk
        else
        {
            grid[10-iy][ix][0] = '*';
            grid[10-iy][ix][1] = ' ';
        }
    }

}

//Draws grid of GameObjects
void View::draw()
{
    for (int i = 0; i < view_maxsize/2 + 1; i++)
    {
        //Print vertical axis
        if (i%2 == 0 && i < 5)
            cout << 20 - 2*i;
        else if (i%2 == 0 && i >5)
            cout << 20 - 2*i << " ";
        else
            cout << "  ";

        //Print grid of pointers
        for (int j = 0; j < view_maxsize/2 + 1; j++)
        {
            cout << grid[i][j][0];
            //Print space or id number
            if (grid[i][j][0] != '.' && grid[i][j][1] != ' ')
                cout << int(grid[i][j][1]);
            else
                cout << grid[i][j][1];
        }
        cout << endl;
    }
    //Print horizontal axis
    cout << "  0   4   8   12  16  20" << endl;
}
