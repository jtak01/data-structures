/* 
 * Station.cpp
 * COMP15 hw2
 * Fall 2019
 * 4/Feburary/2019
 * Jun Sung Tak
 * Implementation of the Station class 
 */

#include "Station.h"

// Constructor
Station::Station(){
	name = "NoName";
    access = false;
}

// Parameterized Constructor
Station::Station(string input_name, bool input_access){
    name = input_name;
    access = input_access;
}

// Function: isEqual
// Input: Statoin
// Returns: Boolean
// Does: Determines if the given station is equal as the 
//       station that this function was called on
bool Station::isEqual(Station s){
    if (name == s.name and access == s.access)
    	return true;
    else 
    	return false;
}

// Function: Print
// Input: ostream
// Returns: None
// Does: Prints the information onto an external file
void Station::print(ostream &outfile){
    if (access == true)
    	outfile << name << " " << "A";
    else 
    	outfile << name << " " << "U";
}


