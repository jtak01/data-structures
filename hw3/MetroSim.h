// MetroSim.h
// Comp15
// Spring 2019
// .h file for MetroSim class
// Also contains Station and Passenger structs
// Written by: Jun Sung Tak
// Date: Feb 21, 2019


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#ifndef _METROSIM_H_
#define _METROSIM_H_

//optional
struct Passenger
{
	int arrival;
	int departure;
	int id;
};

//optional
struct Station
{
	string name;
	int stationNumber;
	vector<Passenger> passengers;
};


class MetroSim{
	public:
		MetroSim();
		MetroSim(string data, string file);
		MetroSim(string data, string file, string cmd);
		~MetroSim();
		void setMaxStations();
		void runSimulation(int);
		
	private:
		void moveStation();
		void directionTracker();
		void printMap();
		void spawnPassenger(int, int);
		void printPassenger(Station);
		void trainLoad();
		void printTrain();
		void trainUnload();
		void printExternal(Passenger);
		void commandHelper();
		void commandInput();
		
		vector<Station> stationVector;
		vector<Passenger> train;
		int currPos;
		int totalPassenger;
		bool moveDirection; 
		ofstream out;							
		ifstream readFile;
		string passFile;
		string inFile;
		string inputs;
		int maxStations;
		bool run;
		
};

#endif