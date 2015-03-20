#include <iostream>
#include "Model.h"
#include "Sharknado.h"
#include "Fish.h"


Sharknado::Sharknado()
{
}

void Sharknado::sweep_away(Model& m1)
{
    int i = 0;
    timer = m1.get_time();
    //Print message 5 seconds before
    if (timer%15 == 10)
        cout << "Early sharknado warning!" << endl;
    //Sweet away fish every 15 seconds
    if (timer%15 == 0 && timer!= 0)
    {
        for (std::list<Fish*>::iterator it = m1.fish_points.begin() ;it != m1.fish_points.end() ;++it)
        {
            char temp = (**it).get_state();
            if (temp!='h')
            {
                int id = (**it).get_id();
                swept_nos[i] = (**it).get_id();
                swept_chars[i] = (**it).get_displaycode();
                cout << "Sharknado swept away " << (**it).get_displaycode() << (**it).get_id() << endl;
                if ((**it).get_displaycode() == 'T')
                {
                    for (std::list<Tuna*>::iterator itTuna = m1.tuna_points.begin(); itTuna != m1.tuna_points.end(); ++itTuna)
                    {
                        int tunaID = (**itTuna).get_id();
                        if (id==tunaID)
                            itTuna = m1.tuna_points.erase(itTuna);
                    }
                }
                it = m1.fish_points.erase(it);
                it--;
                i++;
            }
        }
    }
}

void Sharknado::printout()
{
    //Pint out all the fish that have been swept away
    for (int i = 0; i < 30; i++)
    {
        if (swept_chars[i]=='T' || swept_chars[i] =='S')
        cout << "Swept away " << swept_chars[i] << swept_nos[i] << endl;
    }
}
