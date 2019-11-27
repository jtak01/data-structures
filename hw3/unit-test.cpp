// unit-test.cpp
// Comp15
// Spring 2019
// Unit test file for MetroSim
// This only compiles when all member variables and functions are
// moved to the public portion in the MetroSim.h file
// Written by: Jun Sung Tak
// Date: Feb 21, 2019

#include "MetroSim.h"
#include <iostream>
using namespace std;

string FILENAME = "stations.txt";
string PASSFILE = "passFileTest.txt";

void testSetMax();
void testMove();
void testSpawn();
void testTrain();
void testTrainReverse();

int main()
{
	testSetMax();
	testMove();
	testSpawn();
	testTrain();
	testTrainReverse();
}

void testSetMax()
{
	MetroSim a(FILENAME, PASSFILE);
	a.setMaxStations();
	// I must subtract the size of the vector by one because 
	// the function that reads in stations always reads one extra
	// blank line after the last station
	int stations = a.stationVector.size() - 1;
	if (stations == a.maxStations)
		cout << "setMaxStations works as intended\n";
	else 
		cout << "setMaxStations does not work\n";
}

// Test the moveStations() function. If it works then it means
// directionTracker() function works as well
// Tests if the train first moves forward and then if train reaches
// the last station it reverses its direction
void testMove()
{
	int predictedCurrPos = 2;
	MetroSim a(FILENAME, PASSFILE);
	a.setMaxStations();
	a.directionTracker();
	a.moveStation();
	// Condition to test that the train moves forward
	if (a.currPos == predictedCurrPos){
		a.currPos = a.maxStations;
		a.directionTracker();
		a.moveStation();
		predictedCurrPos = a.maxStations - 1;
		// Condtition to test that the train moves in the other direction
		// after reaching the last station
		if (a.currPos == predictedCurrPos)
			cout << "moveStation works as intended\n";
	}
}

// Test the spawnPassenger() function. If it works it should put the
// passenger into the select station's passenger vector
// Also tests if the variables in the passenger struct is accurate
void testSpawn()
{
	MetroSim a(FILENAME, PASSFILE);
	a.setMaxStations();
	a.spawnPassenger(1, 4);
	// Checks 1st index because spawnPassneger() is supposed to put the 
	// passenger into the passenger vector in the 1st index
	if (a.stationVector[1].passengers[0].id == 1 and
		a.stationVector[1].passengers[0].departure == 4 and
		a.stationVector[1].passengers[0].arrival == 1)
			cout << "spawnPassenger works as intended" << endl;
}

// Tests trainLoad() and trainUnload() functions when the train is 
// going forwards
// Note: trainLoad() and trainUnload() funcitons are called within
// moveStations() function
void testTrain()
{
	MetroSim a(FILENAME, PASSFILE);
	a.setMaxStations();
	// Spawns 1 passenger with id: 1, arrival: 1, departure: 1
	a.spawnPassenger(1, 4);
	a.directionTracker();
	a.moveStation();
	// If trainLoad() works as intended the 0th index of the train
	// vector should contain the passenger with id: 1
	if (a.train[0].id == 1 and a.train.size() == 1)
		cout << "trainLoad when train is going forwards works as intended\n";
	a.moveStation();
	a.moveStation();
	a.moveStation();
	// If trainUnload works properly then the train vector should be empty
	if (a.train.size() == 0)
		cout << "trainUnload when the train is going "
			 << "forwards works as intended\n";
}

// Tests if trainLoad() and trainUnload() functions work properly
// even when train is going backwards
// Note: trainLoad() and trainUnload() funcitons are called within
// moveStations() function
void testTrainReverse()
{
	MetroSim a(FILENAME, PASSFILE);
	// Allows the train to move backwards
	a.moveDirection = false;
	a.setMaxStations();
	a.currPos = a.maxStations - 1;
	// Spawns a passenger at second last station that gets off the train
	// at the third last station
	a.spawnPassenger(a.currPos, a.currPos - 1);
	a.moveStation();
	// Since the train is at the third last station, the passenger should
	// have gotten off and the train vector should be empty at this point
	if (a.train.size() == 0)
		cout << "train functions properly even whengoing backwards\n";
}