// MetroSim.cpp
// Comp15
// Spring 2019
// Implementation of MetroSim.h 
// Contains all functions required to run the MetroSim
// This class manipulates Station and Passenger structs with vectors
//     to simulate a metro running
// Written by: Jun Sung Tak
// Date: Feb 21, 2019

#include "MetroSim.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Default constructor 
MetroSim::MetroSim()
{
	totalPassenger = 0;
	currPos = 1;
	moveDirection = false;
	maxStations = 0;
	passFile = "";
	inFile = "";
	inputs = "";
}

// Parametrized constructor
// This is called when the argc value is 3
// The stations are being read-in in this constructor
MetroSim::MetroSim(string data, string file)
{
	totalPassenger = 0;
	currPos = 1;
	moveDirection = false;
	run = true;
	maxStations = 0;
	passFile = file;
	inFile = data;
	out.open(passFile);
	int counter = 1;
	string station;
	// Reads in stations
	readFile.open(inFile);
	while (!readFile.eof())
	{
		getline(readFile, station);
		Station temp;
		temp.name = station;
		temp.stationNumber = counter;
		stationVector.push_back(temp);
		counter++;
	}
}

// Parametrized constructor
// This is called when the argc value is 4
// The stations are being read-in in this constructor
MetroSim::MetroSim(string data, string file, string cmd)
{
	totalPassenger = 0;
	currPos = 1;
	moveDirection = false;
	run = true;
	maxStations = 0;
	passFile = file;
	inFile = data;
	inputs = cmd;
	out.open(passFile);
	int counter = 1;
	string station;
	// Reads in stations
	readFile.open(inFile);
	while (!readFile.eof())
	{
		getline(readFile, station);
		Station temp;
		temp.name = station;
		temp.stationNumber = counter;
		stationVector.push_back(temp);
		counter++;
	}
}

// Destructor
MetroSim::~MetroSim()
{
	out.close();
	readFile.close();
}

// Input: number of arguments given in main
// Returns: nothing
// Does: Differentiates between when there are 3 and 4 arguments and 
//		 runs the program accordingly
void MetroSim::runSimulation(int arguments)
{
	if (arguments == 4){
		commandInput();
	} else {
		while (run) {
			directionTracker();
			printMap();
			commandHelper();
		}
	}
	cout << "Thanks for playing MetroSim. Have a nice day!\n";
}

// Input: Nothing
// Returns: Nothing
// Does: Takes in keyboard input and calls functions accordingly
void MetroSim::commandHelper()
{
	string command, command1, fileName;
	int d, a;
	cout << "Command : ";
	cin >> command;
	if (command == "m")
	{
		cin >> command1;
		if (command1 == "m"){
			moveStation();
		} else if (command1 == "f") 
			run = false;
	} else if (command == "p") {
		cin >> a >> d;
		spawnPassenger(a, d);
	} else if (command == "f") {
		cin >> fileName;
		out.close();
		out.open(fileName);
		if (!out.is_open()) {
			cerr << "Error: could not open file " << inFile << endl;
			exit(1);
		}
	}	
}

// Input: Nothing
// Returns: Nothing
// Does: Function for when a file with commands are in one of the arguments 
//		 to main. Extracts one line of command each time and calls functions
//		 accordingly
void MetroSim::commandInput()
{
	ifstream cmd;
	cmd.open(inputs);
	while (!cmd.eof())
	{
		directionTracker();
		printMap();
		cout << "Command : ";
		string command, command1, fileName;
		cmd >> command;
		if (command == "m") {
			cmd >> command1;
			if (command1 == "m")
				moveStation();
			else if (command1 == "f")
				run = false;
		} else if (command == "p") {
			int a, d;
			cmd >> a >> d;
			spawnPassenger(a, d);
		} else if (command == "f") {
			cmd >> fileName;
			out.close();
			out.open(fileName);
			if (!out.is_open()) {
				cerr << "Error: could not open file " << inFile << endl;
				exit(1);
			}
		}
	}
}

// Input: Nothing
// Returns: Nothing
// Does: Calls the function that loads and unloads the train. According to
//		 the boolean variable, it makes the train move forward and 
//		 backwards through stations
void MetroSim::moveStation()
{
	trainLoad();
	trainUnload();
	if (moveDirection == false)
	{
		currPos--;
	} else {
		currPos++; 
	}
	return;
}

// Input: Nothing
// Returns: Nothing
// Does: Checks if current position of the train is either 1 or number of 
//		 max stations. Then it manipulates the boolean variable, 
//		 moveDirection, which determines whether the train is going 
// 		 backwards or forwards
void MetroSim::directionTracker()
{
	if (currPos == 1)
		moveDirection = true;
	else if (currPos == maxStations)
		moveDirection = false;
}

// Input: Nothing
// Returns: Nothing
// Does: Prints the map of all stations, all passengers on the train
//		 and all passengers in stations waiting for the train
void MetroSim::printMap()
{
		cout << "Passengers on the train: {";
		printTrain();
		cout << "}" << endl;
		setMaxStations();
	for (int i = 0; i < maxStations; i++)
	{	
		if (currPos == stationVector[i].stationNumber)
		{
			cout << "TRAIN: " << "[" << stationVector[i].stationNumber
				 << "] " << stationVector[i].name 
				 << " {";
			printPassenger(stationVector[i]);
			cout << "}" << endl;
		} else {

			cout << "       " << "[" << stationVector[i].stationNumber 
				 << "] " << stationVector[i].name << " {";
			printPassenger(stationVector[i]);;
			cout << "}" << endl;
		}
	}
	return;
}

// Input: Nothing
// Returns: Nothing
// Does: Sets the maxStations variable to the correct integer
void MetroSim::setMaxStations()
{
	maxStations = stationVector.size() - 1;
}

// Input: arrival and departure 
// Returns: Nothing
// Does: Declares a Passenger struct and assigns the arrival and departure
//	     variable with a and d
void MetroSim::spawnPassenger(int a, int d)
{
	Passenger temp;
	temp.arrival = a;
	temp.departure = d;
	temp.id = totalPassenger + 1;
	stationVector[a].passengers.push_back(temp);
	totalPassenger++;
}

// Input: Station
// Returns: Nothing
// Does: Prints the vector of Passengers that are at Station s
void MetroSim::printPassenger(Station s)
{
	int size = stationVector[s.stationNumber].passengers.size();
	for (int i = 0; i < size; i++)
	{
		cout << "[" << stationVector[s.stationNumber].passengers[i].id 
			 << ", " 
			 << stationVector[s.stationNumber].passengers[i].arrival
			 << "->"
			 << stationVector[s.stationNumber].passengers[i].departure 
			 << "]";
	}
}

// Input: Nothing
// Returns: Nothing
// Does: Loads all the passengers that the train is at
void MetroSim::trainLoad()
{
	int size = stationVector[currPos].passengers.size();
	for (int i = 0; i < size; i++)
	{
		train.push_back(stationVector[currPos].passengers[i]);
	}
	stationVector[currPos].passengers.clear();
}

// Input: Nothing
// Returns: Nothing
// Does: Prints the passengers that are on the train
void MetroSim::printTrain()
{
	int trainSize = train.size();
	for (int i = 0; i < trainSize; i++)
	{
		cout << "[" << train[i].id << ", " << train[i].arrival << "->"
			 << train[i].departure << "]";
	}
}

// Input: Nothing
// Returns: Nothing
// Does: Checks if the passengers that are on the train has arrived to 
//		 their destination. If they did, they are then removed from the 
//		 train
void MetroSim::trainUnload()
{
	int trainSize = train.size();
	for (int i = 0; i < trainSize; i++)
	{
		// When the train is going forwards
		if (moveDirection == true)
		{
			if (train[i].departure - 1 == currPos)
			{
				printExternal(train[i]);
				train.erase(train.begin() + i);
				trainSize = train.size();
				i--;
			}
		// When the train is going backwards
		} else {
			if (train[i].departure + 1 == currPos)
			{
				printExternal(train[i]);
				train.erase(train.begin() + i);
				trainSize = train.size();
				i--;
			}
		}
	}
}

// Input: Passenger
// Returns: Nothing
// Does: Prints the passenger ID and his destination to an external file
void MetroSim::printExternal(Passenger p)
{
	out << "Passenger " << p.id << " left train at station "
		<< p.departure << endl;
}
