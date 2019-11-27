// Dna.cpp
// Comp15
// Spring 2019
// Header file for Dna class  
// Functions and member variables for Dna class
// Written by: Jun Sung Tak
// Date: Mar 13, 2019

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
#include "Node.h"

class Dna {
public: 
	Dna();
	Dna(string file);
	~Dna();
	void commandInput(string);
	Node *root;
	void insert_caller(string);
	void remove_caller(string);
	void deleteAllCaller(Node *node);
	void queryHelper(string, char *arr);
	void print(char *word, Node *node, int, string, bool, int);
	void nodeCountAux();
	void deleteAll(Node *root);
	bool empty(Node *root);
	Node *newNode();
	void insert(string, Node *node);
	int nodeCount(Node *node);
	Node *remove(string toRemove, Node *node, int level);
	void printSeq(char* word, int, string, bool, int);
	bool contains(string, Node *node);
	int calculatePercent(int, string, string);
	void changePassFile(string);
	int index(char);
	bool preFixQ(string, Node *node, char *arr, int, string);
	bool query(string, Node *node, char *word, string, int);
	int calculateHelper(string, string);

private: 
	vector<string> qList;
	string outName;
	ofstream out;
	
	
};