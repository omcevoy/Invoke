/*
* Description: Project 1 (cold calling system)
*
* Author: Owen, Mason, James, Zach, Sam
*
* Date of last update: 1/31/2020
*
* Notes: The main file of the program. Some codes will be repeated for ncurses
* window enviornment, Please refer to code written in StartS to understand ncurses built in functions
*
*/
#include "ColdCallClassList.h"
#include "ColdCallQueue.h"
#include "ColdCallClass.h"
#include "Student.h"
#include "Reporting.h"
#include "RosterIE.h"
#include "statePersistence.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <dirent.h>

using namespace std;

// first menu page
int StartS()
{
    // Set up ncurses environment
    //initzailzing the window
    initscr();
    // No buffering
    cbreak();
    // No printing every input
    noecho();
    // removes cursor
    curs_set(0);

    //setting up window
    int height, width, x, y;
    // to maximum size of current terminal
    getmaxyx(stdscr, y, x);
    height = y;
    width = x;
    // should get us in the middle
    WINDOW * win = newwin(height, width, y - y/1.6, 0);
    // update the screen
    refresh();
    // makes box framework
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    // refresh window
    wrefresh(win);
    // registers key strokes
    keypad(win, TRUE);

    string choices[5] = {"Start a Class Session", "Add a Class", "Delete a Class" , "Term Report", "End of Day"};
    mvwprintw(win, 0, x/2.5, "     InVøke  ");

    int highlight = 0;
    int i, choice;
    //our while loop condition
    bool selected = false;

    // selecting out menu, highlighted moved based on key strokes
    while(!selected)
    {
        // this for loop highlights the current index in which int highlight is at
        for(i = 0; i < 5; i++)
        {
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+1, x/2.5, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        // listening for keyboard interaction
        choice = wgetch(win);
        // switch statement that waits until right key stroke is pressed 
        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 5)
                    highlight = 4;
                break;
            case KEY_RIGHT:
                selected = true;
            default:
                break;
        }
    }
    // end the window and return the thing that was selected (the int index)
    endwin();
    return highlight;


}

// menu for all the class list for running the program (after pressing "Start A Class Session")
// It's only arugnemt is a reference to the class list
int ClassListSR(ColdCallClassList ourclasses)
{
    // Set up ncurses environment
    //initzailzing the window    
    initscr();
    // No buffering
    cbreak();
    // No printing every input
    noecho();
    // removes cursor
    curs_set(0);

    //setting up window
    int height, width, x, y;
    getmaxyx(stdscr, y, x); 
    height = y;
    width = x;
    WINDOW * win = newwin(height, width, y - y/1.6, 0);
    refresh();
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    wrefresh(win);
    keypad(win, TRUE);

    // Gets the list of our classes
    vector <string> choices = ourclasses.getClassList();

    // number of classes
    int length = choices.size();

    mvwprintw(win, 0, x/2.5, "     InVøke  ");
    mvwprintw(win, 1, x/2.5, "Start a Class Session ");


    int highlight = 0;
    int i, choice;
    bool selected = false;

    // selecting out menu, highlighted moved based on key strokes
    while(!selected)
    {
        for(i = 0; i < length; i++)
        {
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+2, x/2.5, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == length)
                    highlight = length - 1;
                break;
            case KEY_RIGHT:
                selected = true;
                break;
            case KEY_LEFT:
                highlight = -1;
                selected = true;
                break;
            default:
                break;
        }
    }

    // end the window and return the thing that was selected
    endwin();
    // this time the return value is the index valur of the class we want. so ourclasses[highlight]
    return highlight;
}

// menu for all the class list for Deleting a class
// It's only arugnemt is a reference to the class list
int ClassListSD(ColdCallClassList ourclasses)
{
    // Set up ncurses environment
    //initzailzing the window
    initscr();
    // No buffering
    cbreak();
    // No pritning every input
    noecho();
    // removed cursor
    curs_set(0);

    //setting up window
    int height, width, x, y;
    getmaxyx(stdscr, y, x);
    height = y;
    width = x;
    // should get us in the middle
    WINDOW * win = newwin(height, width, y - y/1.6, 0);
    refresh();
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    wrefresh(win);
    keypad(win, TRUE);
    // our class list
    vector <string> choices = ourclasses.getClassList();

    int length = choices.size();

    mvwprintw(win, 0, x/2.5, "     InVøke  ");
    mvwprintw(win, 1, x/2.5, "Delete a Class ");


    int highlight = 0;
    int i, choice;
    bool selected = false;

    // selecting out menu, highlighted moved based on key strokes
    while(!selected)
    {
        for(i = 0; i < length; i++)
        {
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+2, x/2.5, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == length)
                    highlight = length - 1;
                break;
            case KEY_RIGHT:
                selected = true;
                break;
            case KEY_LEFT:
                highlight = -1;
                selected = true;
                break;
            default:
                break;
        }
    }

    // end the window and return the thing that was selected
    endwin();
    // almost indentical to classLISTSR however prints "delete a class"
    return highlight;
}

// menu for all the class list for Report
// It's only arugnemt is a reference to the class list
int ClassListSReport(ColdCallClassList ourclasses)
{
    // Set up ncurses environment
    //initzailzing the window
    initscr();
    // No buffering
    cbreak();
    // No pritning every input 
    noecho();
    // removed cursor
    curs_set(0);

    //setting up window
    int height, width, x, y;
    getmaxyx(stdscr, y, x);
    height = y;
    width = x;
    // should get us in the middle
    WINDOW * win = newwin(height, width, y - y/1.6, 0);
    refresh();
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    wrefresh(win);
    keypad(win, TRUE);

    vector <string> choices = ourclasses.getClassList();

    int length = choices.size();

    mvwprintw(win, 0, x/2.5, "     InVøke  ");
    mvwprintw(win, 1, x/2.5, "Term Report  ");


    int highlight = 0;
    int i, choice;
    bool selected = false;

    // selecting out menu, highlighted moved based on key strokes
    while(!selected)
    {
        for(i = 0; i < length; i++)
        {
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+2, x/2.5, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == length)
                    highlight = length - 1;
                break;
            case KEY_RIGHT:
                selected = true;
                break;
            case KEY_LEFT:
                highlight = -1;
                selected = true;
                break;
            default:
                break;
        }
    }

    // end the window and return the thing that was selected
    endwin();
    // simair to the last two functions however prints "Term report"
    return highlight;
}

// program to start the class session
// It's first arugnemt is a reference to the class list, and second argument is the name of the class
int classSession(class ColdCallClass * selectedClass, string className)
{
    // Set up ncurses environment
    //initzailzing the window
    initscr();
    // No buffering
    cbreak(); 
    // doesn't delay the key strokes
    nodelay(stdscr, TRUE);
    // removed cursor
    curs_set(0); 

    //setting up window
    int height, width, x, y;
    getmaxyx(stdscr, y, x);
    height = y;
    width = x;
    // should get us in the middle
    WINDOW * win = newwin(height, width, y - y/1.6, 0);
    refresh();
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    wrefresh(win);
    keypad(win, TRUE);

    // Clearing the window
    string megaString = "     ";
    for (int i = 0; i < 200; i++)
        megaString = megaString + "    ";
    // should get us in the middle
    mvwprintw(win, 0, x/2.5, className.c_str());
    selectedClass->updateRoster(true);
    // getting the queue of the class
    class ColdCallQueue * classQueue = selectedClass->getQueue();
    if (classQueue == nullptr){
        std::cerr << "Failed to get the queue" << '\n';
        return 1;
    }
    std::vector<struct Student *> on_deck;
    // Get the students currently on deck


    int highlight = 0;
    int i, choice;
    bool selected = false;
    // locations where to print the names on deck
    int locations[5] = {(int)(x * .2), (int)(x * .35), (int)(x * .5 ), (int)(x * .65)};
    
    while(!selected)
    {
        // getting the deck
        on_deck = classQueue->getOnDeck(4);
        // going to copy it into here
        vector <string> choices; 
        for (int i = 0; i < 4; i ++)
            choices.push_back(on_deck[i]->first_name + ' ' + on_deck[i]->last_name + '\0');

        for(i = 0; i < 4; i++)
        {
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, 4, locations[i], choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        // get the key stroke
        choice = wgetch(win);

        switch(choice)
        {
            case KEY_LEFT:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_RIGHT:
                highlight++;
                if(highlight == 4)
                    highlight = 3;
                break;
            case KEY_DOWN:
                //Record participation
                // they answered a question (good job :))
                classQueue->removeOnDeck(highlight, ' ');
                mvwprintw(win, 4, locations[i], megaString.c_str());
                highlight = 0;
                break;
            case KEY_UP:
                //Record participation with a flag
                // they got a flag :(
                classQueue->removeOnDeck(highlight, 'X');
                mvwprintw(win, 4, locations[i], megaString.c_str());
                highlight = 0;
                //selected = true;
                break;
            case 32:
                selected = true;
                break;
        }
    }

    endwin(); 
    return -1;
}

// menu to display whether or not the user is certain that they want to do this action
// return either true (for "Yes") or false (for "No")
bool areyousure()
{
    // Set up ncurses environment
    //initzailzing the window
    initscr();
    // No buffering
    cbreak();
    // No pritning every input
    noecho(); 
    // removed cursor
    curs_set(0);

    //setting up window
    int height, width, x, y;
    getmaxyx(stdscr, y, x);
    height = y;
    width = x;
    // should get us in the middle
    WINDOW * win = newwin(height, width, y - y/1.6, 0); 
    refresh();
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    wrefresh(win);
    keypad(win, TRUE);

    string choices[2] = {"Yes", "No"};
    mvwprintw(win, 0, x/2.5, "     InVøke  ");
    mvwprintw(win, 1, x/2.5, "Are you sure you want to delete this class");

    int highlight = 0;
    int i, choice;
    bool selected = false;

    // selecting out menu, highlighted moved based on key strokes
    while(!selected)
    {
        for(i = 0; i < 2; i++)
        {
            if(i == highlight)
                wattron(win, A_REVERSE);
            mvwprintw(win, i+2, x/2.5, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }
        choice = wgetch(win);

        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 2)
                    highlight = 1;
                break;
            case KEY_RIGHT:
                // if they selected no
                if(highlight == 1) 
                {
                    endwin();
                    return FALSE;
                }
                // if not (has to be yes no other choices)
                endwin();
                return TRUE;
            // to go back (IE saying no)
            case KEY_LEFT:  
                endwin(); 
                return FALSE;
            default:
                break;
        }
    }
    // should never get here but just for c++ compile warnings
    endwin();
    return FALSE;


}

vector <string> getClasses() {
    //returns a list of all the files in a directory
    vector <string> classes;
    string path = getPath(2);
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            //convert char* to string
            string dirItem(ent->d_name);
            //ensure file is not . or ..
            if (dirItem[0] != '.' && dirItem != "..") 
                classes.push_back(dirItem);        
        }
        closedir (dir);
    }
    return classes;
}

// this function adds a class name to our class list. 
// NOTE: This does not automatcally look for the roster
//       That still has to be done manually. Please refer to User Documentation
//       It's assumed that the user is used to pressing enter to summit a value
// Takes in ourclasses and possibly puts the name typed in the window into the list. This function will always return -1 (ie take us back to the main menu page)
int addClassname(ColdCallClassList &ourclasses)
{
    // Set up ncurses environment
    //initzailzing the window
    initscr();
    // No buffering
    cbreak(); 
    // No pritning every input
    noecho(); 
    // removed cursor
    curs_set(0); 

    //setting up window
    int height, width, x, y;
    getmaxyx(stdscr, y, x);
    height = y;
    width = x;
    // should get us in the middle
    WINDOW * win = newwin(height, width, y - y/1.6, 0);
    refresh();
    wborder(win, (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ', (int)' ');
    wrefresh(win);
    keypad(win, TRUE);

    mvwprintw(win, 0, x/2.5, "     InVøke  ");
    mvwprintw(win, 1, x/2.5, "Enter Class Name");
    mvwprintw(win, 2, x/2.5, "Class name: ");

    // our string to be "return" (put into the ourclasslist)
    string classname;
    int choice;
    bool selected = false;
    // selecting out menu, highlighted moved based on key strokes
    while(!selected)
    {
        mvwprintw(win, 2, x/2.5 + 12, classname.c_str());
        wrefresh(win);
        choice = wgetch(win);
        switch(choice)
        {
            // if they want to go back into the menu
            case KEY_LEFT:
                endwin();
                return -1;
            // if they press enter (ie are done putting in the class name)
            case 10: 
                ourclasses.addClass(classname);
                endwin();
                return -1;
            // if delete is pressed
            case 127: 
                // Erase last character
                classname.pop_back(); 
                // ncurses makes it so that the information of last character is still in the window since our last char is now '\0' so we write over with a space
                mvwprintw(win, 2, x/2.5 + 12 + classname.size(), " "); 
                wrefresh(win);
                break;
            // by default our character will be out into the end of the string
            case KEY_DOWN:
                break;
            case KEY_RIGHT:
                break;
            case KEY_UP:
                break;
            default: 
                classname.push_back((char)choice);
                wrefresh(win);
                break;
        }
    }

    // this return is for c++ compile warnings
    return -1;
}

// our main function
int main()
{
    // our main data type
    ColdCallClassList ourclasses;
    //load classes 
    ourclasses.loadClasses(); 
    int choice = -1;
    bool endprogram = false;
    vector <string> classlist;
    while(!endprogram)
    {
        switch(choice)
        {
            // start menu
            case -1: 
                // will alwasy start here
                choice = StartS(); 
                break;
            // option 1 "Start A Class Session"
            case 0: 
                choice = ClassListSR(ourclasses);
                // if we do not want to go back to the main menu
                if(choice != -1) 
                {
                    classlist = ourclasses.getClassList();
                    // if there isn't anything there go back to our inital menu
                    if (!classlist.size()){ 
                        choice = 1;
                        break;
                    }
                    string current_class = classlist[choice];
                    //get the class and load the roster 
                    class ColdCallClass * selectedClass = ourclasses.getClass(current_class); 
                    if (selectedClass == nullptr){
                            std::cerr << "Failed to get the class" << '\n';
                            return 0;
                    }
                    string path = getPath(2);
                    vector <string> rosters = getClasses();
                    int verdict = 0;
                    for (int i = 0; i < (int) rosters.size(); i++){
                        //Ensure that the roster exists
                        string fileName = current_class + ".txt";
                        if (fileName == rosters[i]){
                            verdict = 1;
                        }
                    }
                    if (!verdict){
                        //If the roster does not exist, inform the user where it must go and what it must be titled
                        std::cerr << "A roster for " << current_class << " does not exist. Make sure it is in the correct location ~/Documents/Invoke/Rosters and must be titled " << current_class << ".txt" << std::endl;
                        return 0;
                    }
                    path = path + current_class;
                    std::cout << path << std::endl;
                    selectedClass->loadRoster(path);
                    // start up the on deck stuff
                    classSession(selectedClass, current_class); 
                    choice = -1;
                    break;
                }
                break;
            // option 2 "Add A Class"
            case 1: 
                // adding the class name to the list
                choice = addClassname(ourclasses); 
                choice = -1;
                break;
            //option 3 "Delete A Class"
            case 2:  
                // selects which class user would like to delete
                choice = ClassListSD(ourclasses);
                // go back to main page (left keystroke)
                if(choice == -1) 
                    break;
                // double checking
                if(areyousure()) 
                {
                    classlist = ourclasses.getClassList();
                    ourclasses.deleteClass(classlist[choice].c_str());
                }
                // takes us back to the delte class menu (case 2, option 3)
                choice = 2; 
                break;
            // option 4 "Term Report"
            case 3:
                // selects which class user would like the end of the term report for
                choice = ClassListSReport(ourclasses); 
                // if it wasn't left key stroke
                if(choice != -1) 
                {
                    // these lines of codes (inside if) will write the report to ~/Documents/Invoke/InvokeReports directory
                    classlist = ourclasses.getClassList();
                    string className = classlist[choice];
                    class ColdCallClass * selectedClass = ourclasses.getClass(className);
                    string path = getPath(2);
                    path = path + className;
                    selectedClass->loadRoster(path);
                    selectedClass->exportReport(className + "-Report");
                    std::cout << "Exported Term Report. Check your ~/Documents/Invoke/InvokeReports directory" << std::endl;
                    choice = -1;
                    break;
                }
                break;
            // option 5 "End of Day"
            case 4:
                // simply exists the program
                return 1;
        }
    }
    // return is here since c++ gives a compile warning
    return 0;
}
