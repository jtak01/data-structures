/*
 * ArrayList.h
 * COMP15 Hw1 
 * Spring 2019 
 * Jun Sung Tak
 * Interface for Array of Pirates, matey
 * This is the interface for the ArrayList class which
 * runs the main data structure of the entire program
 * 30/Janurary/2019
 */

#include "Pirate.h"


#ifndef ARRAY_H_
#define ARRAY_H_

const int MAX_PIRATES = 100;

class ArrayList
{
public:
    // Default constructor
    ArrayList();
    ~ArrayList();
    // The basic operations:
    // Insert, Delete, and Find
    Pirate find(Pirate, bool &) const;
    void insert(Pirate);
    void remove(Pirate);
    Pirate getNext();

    // Start over at the beginning of the list
    void makeEmpty();
    void resetArray();

    // Return some basic info
    int getLength() const;

    // Print the array
    void print(ofstream& outFileS) const;

private:
    void expand();  
    void shrink();
    int length;
    int size;
    Pirate *pirates;
    int currPos;
};

#endif
