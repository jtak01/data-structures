// DyArr.h
// Header file for the hash table class
// Contains functions to manipulate the hash table
// Jun Sung Tak

#include "HashLinkList.cpp"
#include "FSTree.h"
#include "DirNode.h"

#ifndef ARRAY_H_
#define ARRAY_H_
  
const int INITIAL_SIZE = 3;

class DyArr
{
public: 
	DyArr();
	~DyArr();
	void insertf(string, int, int);
	void printAll();
	void traverse(string);
	void get_data(string, DirNode *node);
	void funnel(string route);
	vector<string> sources;
	string processString(string word);
	bool exists(string word, vector<string> &);
	string getRoute(int);

	HashLinkList *chain;
	int capacity;
	// These variables are public because it is used to determine hash codes
	// for query word in another class
private:
	int numElem;
	int routeCounter;
	void expand();
};

#endif