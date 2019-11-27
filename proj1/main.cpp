// main.cpp
// Comp15
// Spring 2019
// Main file for Dna class
// Calls commandInput function from the Dna class
// Written by: Jun Sung Tak
// Date: Mar 13, 2019

 
#include <iostream>
#include <fstream>

#include "Dna.h"

using namespace std;
 
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: ./SeqMatch [query file] [output location]\n";
		return 0;
	}
	Dna a(argv[2]);
	a.commandInput(argv[1]);
	return 0;
}

