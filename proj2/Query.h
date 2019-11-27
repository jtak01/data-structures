// Query.h
// Header file for the query class. Handles setting up the table and 
// querying different words in the hashtable
// Jun Sung Tak

#include "DyArr.cpp"
#include <fstream>

class Query{
public:
	Query();
	Query(string output);
	void setUp(string route);
	void run();

private:
	void print(int, string);
	void print_with_caps(int, string, string);
	string print_entire_line(int, string);
	void changeOutput(string fileName);
	
	vector<string> roads;
	DyArr a;
	ofstream out;
};