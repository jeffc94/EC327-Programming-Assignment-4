#include <exception>
#include <iostream>
#include "Fish.h"
#include "CartPoint.h"
#include "CartVector.h"
#include "Cave.h"
#include "CoralReef.h"
#include "GameCommand.h"
#include "GameObject.h"
#include "Tuna.h"
#include "View.h"
#include "Model.h"
#include "Shark.h"
#include "Sharknado.h"
#include "InputHandling.h"

using namespace std;

int main()
{
//Make View Object
    View v1 = View();

    //Print header
    cout << "EC327: Introduction to Software Engineering" << endl;
    cout << "Fall 2014" << endl;
    cout << "Programming Assignment 3" << endl;

    //Make Model object, and show initial status and display
    Model m1 = Model();
    m1.show_status();
    m1.display(v1);
    Sharknado s1 = Sharknado();

    //Initialize command variable
    char command;

    //Run program until quit command is given


    //try
    //{
    do
    {
        //Prompt user for command
        cout << "Enter a command: ";
        cin >> command;

        try
        {
            if (command != 's' && command != 'e' && command != 'f' && command != 'z' && command != 'g' &&
                command != 'r' && command != 'q' && command != 'a' && command != 'n' && command != 'S' &&
                command != 'R')
                throw InvalidInput("Not a proper command");

        //Do corresponding function depending on command character and show display afterwards
        switch (command)
        {
        case 's':
            do_swim_command(m1);
            m1.display(v1);
            break;
        case 'e':
            do_eat_command(m1);
            m1.display(v1);
            break;
        case 'f':
            do_float_command(m1);
            m1.display(v1);
            break;
        case 'z':
            do_zoom_command(m1);
            m1.display(v1);
            break;
        case 'g':
            do_go_command(m1);
            m1.display(v1);
            break;
        case 'r':
            do_run_command(m1);
            m1.display(v1);
            break;
        case 'a':
            do_attack_command(m1);
            m1.display(v1);
            break;
        case 'n':
            do_new_command(m1);
            m1.display(v1);
            break;
        case 'S':
            do_save_command(m1);
            m1.display(v1);
            break;
        case 'R':
            do_restore_command(m1);
            m1.display(v1);
            break;
        case 'q':
            cout << "Terminating program" << endl;
            s1.printout();
            return 0;
        }
    }
    catch (InvalidInput& except)
    {
        //Display invalid response
        cout << "Invalid Input - " << except.msg_ptr << endl;
        //Ignore rest of input
        cin.clear();
        cin.ignore(100,'\n');
    }
    s1.sweep_away(m1);
    }while (command != 'q');
}
