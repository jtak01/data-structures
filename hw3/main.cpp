// main.cpp
// Comp15
// Spring 2019
// Driver for MetroSim
// Written by: Jun Sung Tak
// Date: Feb 21, 2019

#include <iostream>
#include <fstream>
#include <string>
#include "MetroSim.h"
using namespace std;

int main(int argc, char* argv[]){
	if (argc < 3 or argc > 4)
	{
		cerr << "Usage: MetroSim stationsFile passFile [commands]\n";
		return 0;
	}
	// Two different cases depending upon number of args given
	if (argc == 4){
		MetroSim a(argv[1] ,argv[2], argv[3]);
		a.setMaxStations();
		a.runSimulation(argc);
	} else {
		MetroSim a(argv[1], argv[2]);
		a.setMaxStations();
		a.runSimulation(argc);
	}
	return 0;
}

