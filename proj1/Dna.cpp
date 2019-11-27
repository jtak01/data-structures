// Dna.cpp
// Comp15
// Spring 2019
// Implementation of Dna.h 
// Contains all functions required to run the Dna sequencing program SeqMatch
// This class manipulates trie to insert, remove, and query DNA sequences
// Also uses vector when comparing query sequences
// Written by: Jun Sung Tak
// Date: Mar 13, 2019

#include <iostream>
#include <string>
#include "Dna.h"
#include <fstream>
#include <cmath>

using namespace std;
 
const string INSERT = "i";
const string REMOVAL = "r";
const string NUM_NODES = "n";
const string PRINT = "p";
const string DELETE = "d";
const string PASS_FILE = "f";
const string PREFIX = "pq";
const string QUERY = "q";

const int NUMCHILD = 4;
const int ARRSIZE = 999999;

// Constructor
Dna::Dna()
{
	root = newNode();
	outName = "";
}

// Paramaterized Constructor
Dna::Dna(string file)
{
	root = newNode();
	outName = file;
	out.open(outName);
	if (!out.is_open())
	{
		cout << "ERROR: File cannot be opened" << endl;
		exit(0);
	}
}

//Destructor
Dna::~Dna()
{
	deleteAll(root);
	out.close();
}

// Helper function for insert
// Parameter: string word
// Returns: nothing
// Does: Calls the insert function which inserts a given sequence into the 
//	     trie
void Dna::insert_caller(string word)
{
	// If the trie is empty this condition re-instantiates the root so that
	// the program can keep going on
	if (root == NULL){
		root = newNode();
		insert_caller(word);
		return;
	}
	if (contains(word, root) == true)
		out << word << " was previously inserted\n";
	else if (contains(word, root) == false)
		out << word << " inserted\n";
	insert(word, root);
}

// Insert function
// Parameter: string word and Node
// Returns: Nothing
// Does: Inserts the given sequence into the trie. Usually starts from root
//		 (Node *node will be root)
void Dna::insert(string word, Node *node)
{
	if (word != "" and node -> child[index(word[0])] == NULL){	
		node -> child[index(word[0])] = newNode();
		node -> child[index(word[0])] -> data = word[0];
		Node *temp = node -> child[index(word[0])];
		word.erase(word.begin());
		insert(word, temp);
	} else if (word != "" and node -> child[index(word[0])] != NULL){
		node = node -> child[index(word[0])];
		word.erase(word.begin());
		insert(word, node);
	} else if (word == ""){
		node -> end = true;
	}
	return;
}

// Contains function
// Parameter: String toFind and Node
// Returns: Bool of whether the given sequence is in the trie or not
// Does: Goes through the entire trie and sees if the given sequence exits
//		 within the trie starting from given node (which will be root)
bool Dna::contains(string toFind, Node *node)
{
	int length = toFind.size();
	for (int i = 0; i < length; i++)
	{
		if (node -> child[index(toFind[i])] == NULL)
			return false;
		node = node -> child[index(toFind[i])];
	}
	if (node != NULL and node -> end == true)
		return true;
	else 
		return false;
}

// newNode function
// Parameter: None
// Returns: Node
// Does: Declare and initializes all the variables of the node struct
Node *Dna::newNode()
{
	Node *temp = new Node;
	for (int i = 0; i < NUMCHILD; i++)
		temp -> child[i] = NULL;

	temp -> data = '0';
	temp -> end = false;
	return temp;
}

// index function
// Parameter: character
// Returns: Integer
// Does: Returns the corresponding index for a given character in int.
//		 (A = 0, C = 1, G = 2, T = 3)
int Dna::index(char i)
{
	if (i == 'A')
		return 0;
	if (i == 'C')
		return 1;
	if (i == 'G')
		return 2;
	if (i == 'T')
		return 3;
	else 
		return -1;
}

// Print function
// Parameter: Array of character, Node, int index, string original, 
//			  bool query, int ind
// Many parameters are used for other functions such as prefix query and query
// Ex: if query == true then this function is used for query
// Returns: Nothing
// Does: Prints the entire trie in alphabetical order
void Dna::print(char *word, Node *node, int index, string original, 
				bool query, int ind)
{
	if (node == NULL){
		return;
	}
	if (node != NULL and node -> end == true){
		printSeq(word, index, original, query, ind);
	}
	for (int i = 0; i < NUMCHILD; i++){
		if (node -> child[i] != NULL){
			word[index] = node -> child[i] -> data;
			print(word, node -> child[i], index + 1, original, query, ind);
		}
	}
}

// printSeq function
// Parameter: Array of charjacter, int index, string original, bool query
//			  , int ind
// Multple parameters work the same way as it does for print function
// Returns: Nothing
// Does: Prints out the given sequences or stores specfic sequences into a 
//		 vector for query
void Dna::printSeq(char *word, int index, string original, bool query, 
				   int ind)
{
	if (query)
	{
		string seq = original.substr(0, ind);
		for (int j = 0; j < index; j++)
		{
			seq = seq + word[j];
		}
		qList.push_back(seq);
		return;
	}
	if (original != "")
		out << original;
	for (int i = 0; i < index; i++){
		out << word[i];
	}
	out << endl;
}

// nodeCountAux function
// Parameter: None
// Returns: Nothing
// Does: Calls nodeCount function and prints the output
void Dna::nodeCountAux()
{
	// Subtract by 1 because the nodeCount function counts the root as a node
	// when I don't want it to
	int nodes = nodeCount(root) - 1;
	out << "There are " << nodes << " nodes in the database\n";
	return;
}

// nodeCount function
// Parameters: Node node
// Returns: int of total nodes in trie
// Does: Counts the number of non NULL nodes in trie
int Dna::nodeCount(Node *node)
{
	int iter = 0;
	if (node == NULL)
		return iter;
	iter = 1;
	for (int i = 0; i < NUMCHILD; i++){
		if (node -> child[i] != NULL)
			iter = iter + nodeCount(node -> child[i]);
	}
	return iter;
}

// Remove function
// Parameters: Node node, string toRemove, int level
// node is where it starts counting, toRemove is the string to be removed
// int level is used to match the number of nodes in sequence to the length
// of given word
// Returns: Node
// Does: Deletes the given sequence from trie
Node *Dna::remove(string toRemove, Node *node, int level)
{
	int stringSize = toRemove.size();
	if (node == NULL)
		return NULL;
	// To indicate to the function that it is on the last node of the given
	// given sequence
	if (level == stringSize)
	{
		if (node -> end == true)
			node -> end = false;
		if (empty(node))
		{
			delete node;
			node = NULL;
		}
		return node;
	}
	node -> child[index(toRemove[level])] = 
	remove(toRemove, node -> child[index(toRemove[level])], level + 1);
	if (empty(node) and !node -> end)
	{
		delete node;
		node = NULL;
	}
	return node;
}

// Remove_caller function
// Parameters: String toRemove
// Returns: Nothing
// Does: Calls the remove function with the given string
void Dna::remove_caller(string toRemove)
{
	if (contains(toRemove, root) == true)
		out << toRemove << " removed\n";
	else if (contains(toRemove, root) == false)
		out << toRemove << ": No match found\n";
	remove(toRemove, root, 0);
}

// empty function
// Parameters: Node
// Returns: Bool of whether the node is empty or not
// Does: Checks the four children of node. If all are NULL then node is empty
bool Dna::empty(Node *node)
{
	for (int i = 0; i < NUMCHILD; i++){
		if (node -> child[i] != NULL)
			return false;
	}
	return true;
}

// DeleteAll function
// Parameters: Node
// Returns: None
// Does: Goes through the trie and deletes all existing nodes. Sets root to 
//	     NULL
void Dna::deleteAll(Node *node)
{
	if (node == NULL)
        return;
    for (int i = 0; i < NUMCHILD; i++)
    {
    	if (node -> child[i] != NULL)
    		deleteAll(node -> child[i]);
    }
    delete node;
    root = NULL;
    return;
}

// DeleteAllCaller function
// Parameters: Node
// Returns: Nothing
// Does: Calls deleteAll with given root and then prints out the number of
//		 nodes in the trie to verify nodes have been deleted
void Dna::deleteAllCaller(Node *node)
{
	deleteAll(node);
	out << "There are " << nodeCount(root) << " nodes in the database\n";
}

// commandInput function
// Parameters: String file
// Returns: Nothing
// Does: Driver function for the whole program. Reads in the query file and
//		 calls the neccessary functions
void Dna::commandInput(string file)
{
	ifstream cmd;
	cmd.open(file);
	while(!cmd.eof())
	{
		string command, seq;
		cmd >> command;
		if (command == INSERT){
			cmd >> seq;
			insert_caller(seq);
		}
		if (command == REMOVAL){
			cmd >> seq;
			remove_caller(seq);
		}
		if (command == NUM_NODES){
			nodeCountAux();
		}
		if (command == PRINT){
			char word[ARRSIZE];
			print(word, root, 0, "", false, 0);
		}
		if (command == DELETE)
			deleteAllCaller(root);		
		if (command == PASS_FILE){
			cmd >> seq;
			changePassFile(seq);
		}
		if (command == PREFIX){
			cmd >> seq;
			char arr[ARRSIZE];
			preFixQ(seq, root, arr, seq.size(), seq);
		}
		if (command == QUERY){
			cmd >> seq;
			char arr[ARRSIZE];
			queryHelper(seq, arr);
		}
	}
	cmd.close();		
}

// changePassFile function 
// Parameters: String file
// Returns: Nothing
// Does: Changes the outfile to the new file that is given as a string
void Dna::changePassFile(string file)
{
	out.close();
	out.open(file);
	if (!out.is_open()) {
		cout << "ERROR: File cannot be opened" << endl;
		exit(0);
	}
	out << "Output file has been change to " << file << endl;
}

// preFixQ function
// Parameters: String word, Node, character array, int length of string,
//		       string original (original word that was given)
// Returns: Boolean of whether there is a matching prefix in the trie
// Does: Searches the trie until the entire given prefix was found
//		 Then it proceeds to print all the sequences from the last node of
//	     the prefix
bool Dna::preFixQ(string word, Node *node, char *arr, int length, string orig)
{
	if (node -> child[index(word[0])] == NULL)
	{
		out << orig <<": No match found\n";
		return false;
	}
	if (node -> child[index(word[0])] != NULL and length != 0)
	{
		Node *temp = node -> child[index(word[0])];
		word.erase(word.begin());
		return preFixQ(word, temp, arr, length - 1, orig);
	}
	if (length == 0)
	{
		print(arr, node, 0, orig, false, 0);
		return true;
	}
	return true; 
}

// Query function
// Parameters: String word, Node, character array, string original word, int 
//			   ind (index of the farthest matching character)
// Returns: Whether or not there was a valid match in the trie
// Does: Looks until the prefix is different. Then it will run the query 
//    	 operation with the shortest sequence (calculating percetn match)
bool Dna::query(string word, Node *node, char *arr, string original, int ind)
{
	if (word.empty())
	{
		print(arr, node, 0, original, true, ind);
		return true;
	}
	if (node -> child[index(word[0])] == NULL)
	{
		print(arr, node, 0, original, true, ind);
		return true;
	}
	if (node -> child[index(word[0])] != NULL)
	{
		Node *temp = node -> child[index(word[0])];
		word.erase(word.begin());
		return query(word, temp, arr, original, ind + 1);
	}
	return true;
}
 
// QueryHelper function
// Parameters: String word and character array
// Returns: Nothing
// Does: Calls the query function and then calls calculatePercent function
void Dna::queryHelper(string word, char *arr)
{
	qList.clear();
	if (root -> child[index(word[0])] == NULL or root == NULL){
		out << word << ": No match found\n";
		return;
	}
	query(word, root, arr, word, 0);
	int length = qList.size();
	int smallestLength = qList[0].size();
	int index = 0;
	for (int i = 0; i < length; i++)
	{
		int tempLength = 0;
		tempLength = qList[i].size();
		if (smallestLength > tempLength){
			index = i;
			smallestLength = tempLength;
		}
	}
	out << "Match found: " << qList[index] << " " 
		 << calculatePercent(smallestLength, word, qList[index]) 
		 << "%" << endl;
}

// calculatePercent function
// Parameters: int smallestLength of shortest sequence, string word 
//			   (Given query), and string vecWord (Word that matches the most)
// Returns: Int of the percentage match
// Does: Calculates the %match of the query
int Dna::calculatePercent(int smallestLength, string word, string vecWord)
{
	double percent = 0.0;
	double wordLength = word.size();
	double totalLength = smallestLength; // length of word found
	double lengthOfQuery = calculateHelper(word, vecWord); // length of common chars
	if (wordLength >= totalLength)
		percent = (lengthOfQuery / wordLength) * 100;
	else if (wordLength < totalLength)
		percent = (lengthOfQuery / totalLength) * 100;
	int percentInInt = round(percent);
	return percentInInt;
}

// calculateHelper function
// Parameters: String word, string foundWord
// Returns: Int of number of characters two strings have in common from 
//			beginning
// Does: Keeps comparing character by character of the two strings until
// 		 they are different 
int Dna::calculateHelper(string word, string foundWord)
{
	int i = 0;
	int counter = 0;
	while(word[i] == foundWord[i]){
		counter++;
		i++;
	}
	return counter;
}

