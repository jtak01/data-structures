/*
 * Station.h
 * COMP15 hw2
 * Spring 2019
 * 4/Feburary/2019
 * Jun Sung Tak
 * Implementation of the Station class for homework 2
 * The station class deals with the station object. It includes 
 * functions such as print, isEqual, getAccess, and getName
 */

#include <fstream>
#include <string>
using namespace std;

#ifndef STATION_H_
#define STATION_H_

class Station
{
public:
    Station();                      //Constructor 
                                    //Creates a station with name "NoName" 
                                    //and accessibility "False"
    Station(string, bool);          //constructor that also sets the station 
                                    //name and accessibility

    void print(ostream &);          //Prints the information on the station
    bool isEqual(Station);//Returns true if both stations have the 
                                    //same name and accessibility
    bool getAccess() {              //Getter for access
        return access;
    };
    string getName(){               //Getter for name
        return name;
    }


private:
    string name;
    bool access;
};

#endif
