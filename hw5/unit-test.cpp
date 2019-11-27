#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Graph.h"
#include "Actor.h"
#include "SixDegree.h"

using namespace std;
 
void actor_test();


int main()
{
	SixDegree h;
	h.populate_graph();
	//Graph<string> d(p);

	int i = h.get_num();
	cout << i <<  endl;
	cout << h.p.get_vertex(0) << endl;
	cout << h.p.get_vertex(1) << endl;;
	cout << h.p.get_vertex(171) << endl;
	cout << h.p.get_vertex(170) << endl;
	h.BFS(h.p.get_vertex(169), h.p.get_vertex(168), cout);
	cout << "Testing connect: " << h.p.get_vertex(170).connect(h.p.get_vertex(169)) << endl;
}

void actor_test()
{
	Actor a("FG");
	Actor b("GF");
	a.insert_movie("AAAA");
	a.insert_movie("vATT");
	a.insert_movie("GGAFS");
	a.insert_movie("W");
	b.insert_movie("a");
	b.insert_movie("The bee movie");
	b.insert_movie("AGWESB");
	b.insert_movie("GGGG");
	cout << a.connect(b) << endl;
}