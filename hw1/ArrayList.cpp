/*
 * Array.cpp
 * COMP15 Hw1
 * Spring 2019
 * Jun Sung Tak
 * Implementation for Arrrrrrray of Pirates
 * 30/Janurary/2019
 */

#include "ArrayList.h"
#include <iostream>

using namespace std;

// Default constructor
// Length and current position default to 0
ArrayList::ArrayList(){
    pirates = new Pirate [MAX_PIRATES];
    length = 0;
    size = MAX_PIRATES;
    currPos = 0;
}

// Destructor for ArrayList
// Member variables are set to 0 and the dynamically allocated
// array is freed from the heap
ArrayList::~ArrayList(){
    delete [] pirates;
    length = 0;
    size = 0;
    currPos = 0;
}

// Inputs: Pirate object, bool by reference
// Returns: Pirate object
// Does: Looks for pirate in the array, modifies bool if found
//       Returns the object from the list and not the passed one
//       (In case they're different.)
Pirate ArrayList::find(Pirate p, bool &found) const{
    int location = 0;
    while ((location < length) && !found){
        if (p == pirates[location]){
            found = true;
            p = pirates[location];
            break;
        }
        location++;
    }
    return p;
}

// Inputs: Pirate object
// Returns: Nothing
// Does: Adds Pirate to end of array, increases length
void ArrayList::insert(Pirate p){
    for (int i = 0; i < length; i++)
    {
        if (p == pirates[i])
            return;
    }
    if (size == length)
    {
        expand();
    }
    pirates[length] = p;
    length++;
}

// Inputs: Pirate object
// Returns: Nothing 
// Does: Deletes pirate, shifts everything else over, and
//       shinks the array if length goes below half of 
//       size
void ArrayList::remove(Pirate p){
    for (int i = 0; i < length; i++)
    {
        if (pirates[i] == p)
        {
            for (int j = i; i < length - 1; j++)
            {
                pirates[j] = pirates[j + 1];
            }
            length--;
            return;
        }
    }
    if (length <= size / 2)
        shrink();
   
}   

// Input: None
// Returns: Pirate object
// Does: Returns pirate at currPos
//       Increments currPos, but wraps around
Pirate ArrayList::getNext(){
    Pirate p = pirates[currPos];
    currPos = (currPos + 1) % length;
    return p;
}

// Input: none
// Returns: none
// Does: sets length to 0 (memory not modified)
void ArrayList::makeEmpty(){
    length = 0;
}

// Input: none
// Returns: none
// Does: sets currPos to 0 
void ArrayList::resetArray(){
    currPos = 0;
}

// Input: ofstream outFile, const
// Returns: none
// Does: Prints array from 0 to length onto a seperate file
void ArrayList::print(ofstream &outFile) const {
    for (int i = 0; i < length; i++){
        pirates[i].print(outFile);
        if (i < length - 1)
            outFile << ", ";
    }

}

// Input: none, const
// Returns: int
// Does: Returns the value in length attribute
int ArrayList::getLength() const {
    return length;
}

// Input: none
// Returns: none
// Does: Expands the total size of the array (twice as big)
void ArrayList::expand(){
    int morePirate = (size * 2);
    Pirate *temp = new Pirate [morePirate];
    cout << "Expand to " << morePirate << endl;
    for (int i = 0; i < size; i++)
    {
        temp[i] = pirates[i];
    }
    size = morePirate;
    delete [] pirates;
    pirates = temp;
}

// Input: none
// Returns: none
// Does: Shinks the total size of the array (half as small)
void ArrayList::shrink(){
    int lessPirate = size / 2;
    Pirate *temp = new Pirate [lessPirate];
    cout << "Contract to " << lessPirate << endl;
    for (int i = 0; i < lessPirate; i++)
    {
        temp[i] = pirates[i];
    }
    size = lessPirate;
    delete [] pirates;
    pirates = temp;
}