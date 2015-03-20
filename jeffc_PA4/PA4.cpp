//
//  main.cpp
//  PA4 --- Under The Sea
//
//  https://www.youtube.com/watch?v=OosYFs3cyZ8
//

#include <iostream>
#include <exception>

#include "CartVector.h"
#include "CartPoint.h"
#include "GameObject.h"
#include "CoralReef.h"
#include "Cave.h"
#include "Fish.h"
#include "Model.h"
#include "GameCommand.h"
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

    //Initialize command variable
    char command;

    //Run program until quit command is given
    do
    {
        //Prompt user for command
        cout << "Enter command: ";
        cin >> command;
        try
        {
            if (command != 's' && command != 'e' && command != 'f' && command != 'z' && command != 'g' &&
                command != 'r' && command != 'q' && command != 'a' && command != 'n')
                    throw command;

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
        case 'q':
            cout << "Terminating program" << endl;
            return 0;
        }
        }
        catch (InvalidInput& except)
        {
            cout << "Invalid Input - " << except.msg_ptr << endl;
            cout << "Enter a command: ";
            cin >> command;
        }
    }
    while (command != 'q');
}

