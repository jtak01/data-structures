/*
 * LinkedList.h
 * COMP15 hw2
 * Spring 2019
 * 4/Feburary/2019
 * Jun Sung Tak
 * Interface for Linked List of Green Line Extension Stations
 * This class provides all the functionality that has to do with
 * the linked list
 */

#include "NodeType.h"
#include "Station.h"
#include <fstream>

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

class LinkedList
{
public:
    LinkedList();                                   // Default constructor
    ~LinkedList();                                  // Default constructor
    LinkedList & operator = (const LinkedList &);   // Assignment Operator
    LinkedList(const LinkedList &);                 // copy constructor. 
                                            // It creates a new list that is 
                                            // identical to the one given


    void insertStation(Station);           // Inserts a station into the list
    void removeStation(Station);           // Removes a station from the list
    void makeEmpty();                      // Empties the list
    void resetCurrPos();
    Station getNextStation();             // Gives a new station

    bool isCurrPosNull() const;
    int getLength() const;                 // Returns the length of the list
    void print(ostream &);                  // Print the list of stations 


private:
    int calculateDistance(Station);  // Takes care of calculating distance
                                     // from the given station to the last 
                                     // station (Was not in the spec)
    int length;
    NodeType *head;
    NodeType *currPos;
};

#endif
