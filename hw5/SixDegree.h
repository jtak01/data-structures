#include <iostream>
#include "Graph.h"
#include "Queue.cpp"
#include <string>

using namespace std;

class SixDegree{
public:
	SixDegree();

	void populate_graph();
	void run(istream &in, ostream &out);
	void BFS(Actor a, Actor b, ostream &out);
	int get_num();
	Graph<Actor> p;
private: 
	
	

};