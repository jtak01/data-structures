// DyArr.cpp
// Implementation of DyArr.h 
// Handles the dynamic hash table
// Jun Sung Tak

#include "DyArr.h"
#include "Node.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <functional>

using namespace std; 

// Default constructor
DyArr::DyArr()
{
	chain = new HashLinkList [INITIAL_SIZE];
	capacity = INITIAL_SIZE;
	routeCounter = 0;
	numElem = 0;
}

// Destructor
DyArr::~DyArr()
{
	for (int i = 0; i < capacity; i++)
	{
		chain[i].burn_link();
	}
	delete [] chain;
	capacity = 0;
	numElem = 0;
}

// insertf()
// Inserts a given word, line number, and paths index, into the hashtable
// Parameters: string word, int line, int counter <- the paths index
// Return: None
void DyArr::insertf(string word, int line, int counter)
{
	if (word == "" or word == " ")
		return;
	double expand_factor = numElem / capacity;
	if (expand_factor >= 0.75)
		expand();
	string hashWord = word;
	transform(hashWord.begin(), hashWord.end(), hashWord.begin(),::tolower);
	int index = hash<string>{}(hashWord) % capacity;
	bool found = false;
	Node *temp = chain[index].find_node(hashWord, found);
	if(!found){
		chain[index].insert(word, line, counter);
		numElem++;
	} else {
		temp->info.push_back(word);
		temp->lineNum.push_back(line);
		temp->route.push_back(counter);
		numElem++;
	}
}

// printAll()
// This function is not used in the gerp program. This existed so that I can 
// test whether the words were getting inserted into the right indicies. 
// Parameters: None
// Returns: None
void DyArr::printAll()
{
	cout << "Printing all\n";
	for (int i = 0; i < capacity; i++)
	{
		if (!chain[i].is_empty())
			chain[i].print(cout);
		else 
			cout << "Empty Linked List\n";
	}
}

// expand()
// Function to expand the dynamic hash table. Every entry in the old hashtable
// is re-hashed and then inserted again depending on the size of the array
// Paramters: None
// Returns: None
void DyArr::expand()
{
	int old_size = capacity;
	int new_size = capacity * 2;
	HashLinkList *temp = new HashLinkList [new_size];
	for (int i = 0; i < old_size; i++)
	{
		if (!chain[i].is_empty()){
			for (int j = 0; j < chain[i].get_length(); j++){
				vector<string> word = chain[i].get_value_at(j) -> info; // fix
				vector<int> line = chain[i].get_value_at(j) -> lineNum; // fix
				vector<int> path = chain[i].get_value_at(j) -> route;
				Node *node = new Node;
				node->info = word;
				node->lineNum = line;
				node->route = path;
				node->next = NULL;
				string hashWord = word[0];
				transform(hashWord.begin(), hashWord.end(), hashWord.begin(),::tolower);
				int index = hash<string>{}(hashWord) % new_size;
				temp[index].insert_by_node(node);
			}
		}
	}
	capacity = new_size;
	for (int i = 0; i < old_size; i++)
	{
		chain[i].burn_link();
	}
	delete [] chain;
	chain = temp;
}

// traverse()
// Function caller for traversing through the directory and loading all the
// files
// Parameters: string root <- directory to start looking from
// Returns: None
void DyArr::traverse(string root)
{
	FSTree file = FSTree(root);
	get_data(root, file.getRoot());
}

// get_data()
// Recursively traverses the given directory and extracts information from all 
// files. 
// Parameters: string root, DirNode *node
// DirNode class was given to us so that we can access directories from the 
// program. 
void DyArr::get_data(string root, DirNode *node)
{
	for (int i = 0; i < node -> numSubDirs(); i++)
	{
		get_data(root + "/" + node -> getSubDir(i) -> getName(), 
			     node -> getSubDir(i));
	}
	for (int j = 0; j < node -> numFiles(); j++)
	{
		string route = root + "/" + node -> getFile(j);
		funnel(route);
	}
}

// funnel()
// Given a file, inserts every single word into the hashtable
// Parameters: string route <- location of the file to read
// Returns: None
void DyArr::funnel(string route)
{
	sources.push_back(route);
	//cout << "Funnel running\n";
	ifstream data;
	data.open(route);
	//cout << fileName << " in " << route << endl;
	if (!data.is_open()){
		cout << "Could not build index, exiting.\n";
		exit(0);
	}
	string temp;
	int counter = 0;	// Used to keep track of line numbers
	while (!data.eof())
	{
		getline(data, temp);
		counter++;
		stringstream ss(temp);
		
		string word;
		vector<string> duplicate;	// Vector used to make sure that the same
									// word on the same line does not get 
									// inserted twice
		while(!ss.eof())
		{
			ss >> word;
			word = processString(word);
			if (!exists(word, duplicate)){
				insertf(processString(word), counter, routeCounter);
				duplicate.push_back(word);
			}
		}
		duplicate.clear();
	}
	data.close();
	routeCounter++;	// Counter used to keep track of the path index
}

// processString()
// Strips all the non-alphabet and non-digit characters of a given string
// Parameters: string word
// Returns: word that qualifies to be a word (Starts and ends with either 
// an alphabet or a digit)
// From phase 1 of the project but was modified a little bit
string DyArr::processString(string word)
{
	if (word == ""){
		return word;
	}
	int length = word.length();
	int startIndex = 0, endIndex = -1;
	for (int i = 0; i < length; i++)
	{
		if (isdigit(word[i]) or isalpha(word[i])){
			startIndex = i;
			i = length;
		}
	}
	for (int j = length; j > -1; j--)
	{
		if (isdigit(word[j]) or isalpha(word[j])){
			endIndex = j;
			j = -1;
		}
	}
	int lengthOfString = endIndex - startIndex + 1;

	return word.substr(startIndex, lengthOfString);
}

// getRoute()
// Function to help copy over the route vector
// Parameters: int index
// Returns: string of the path that is stored in the index of the path vector
string DyArr::getRoute(int index)
{
	return sources[index];
}

// exists()
// Helper function to determine if the given word on a line was already 
// inserted into the hashtable beforehand.
// Parameters: string word, vector<string> &arr <- passes the vector by 
// reference
// Returns: Bool wether the given word exists in the hash table or not
bool DyArr::exists(string word, vector<string> &arr)
{
	int length = arr.size();
	for(int i = 0; i < length; i++)
	{
		if(arr[i] == word)
			return true;
	}
	return false;
}