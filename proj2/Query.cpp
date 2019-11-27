// Query.cpp
// Implementation of Query.h. 
// Utilizes the Hashtable to query words
// Jun Sung Tak

#include "Query.h"
#include "Node.h"
#include <algorithm>

using namespace std;

// Constructor
Query::Query(string output)
{
	out.open(output);
	if (!out.is_open())
	{
		cout << "Could not open file\n";
		exit(0);
	}
}

// setUp()
// Sets up the hashtable and reads in all files
// from the given directory
// Parameters: string route <- directory to start searching from
void Query::setUp(string route)
{
	a.traverse(route);
	roads = a.sources;
}

// run()
// Main loop to keep taking query requests
// Parameters: None
// Returns: None
void Query::run()
{
	bool run = true;
	while (run)
	{
		cout << "Query? ";
		string query;
		string file;
		string word;
		cin >> query;
		if (query == "@q" or query == "@quit" or cin.eof())
			break;
		else if (query == "@i" or query == "@insensitive"){
			cin >> word;
			string original = word;
			transform(word.begin(), word.end(), word.begin(),::tolower);
			//word = a.processString(word);
			int index = hash<string>{}(word) % a.capacity;
			print(index, word);
		} else if (query == "@f"){
			cin >> file;
			changeOutput(file);
		} else {
		 	query = a.processString(query);
			string lowerVersion = query;
			transform(lowerVersion.begin(), lowerVersion.end(), 
					  lowerVersion.begin(),::tolower);
			int index = hash<string>{}(lowerVersion) % a.capacity;
			print_with_caps(index, lowerVersion, query);
		}
		cout << endl;
	}
	cout << "Goodbye! Thank you and have a nice day\n";
}

// print_with_caps()
// Query for case sensitive search
// Parameters: int index, string lowerWord, string upperWord
// lowerWord is the lower case version of the word and upperWord is the 
// original (word with the correct capitalization)
// Returns: None
void Query::print_with_caps(int index, string lowerWord, string upperWord)
{
	int counter = 0;
	bool aux = false;
	Node *temp = a.chain[index].find_node(lowerWord, aux);
	if (aux == false)
	{
		out <<"query not found\n";
		return;
	}
	for (int i = 0; i < int(temp->info.size()); i++)
	{
		if (temp->info[i] == upperWord)
		{
			string path = roads[temp->route[i]];
			out << path << ":" << temp->lineNum[i] << ": "
				 << print_entire_line(temp->lineNum[i], path) << endl;
			counter++;
		}
	}
	if (counter == 0){
		out << "query not found\n";
	}
}

// print()
// Query for case insensitive search
// Parameters: int index, string word
// Returns: None
void Query::print(int index, string word)
{
	bool aux = false;
	Node *temp = a.chain[index].find_node(word, aux);
	if (aux == false)
	{
		out << "query not found\n";
		return;
	}
	for (int i = 0; i < temp->info.size(); i++)
	{
		int routeIndex = temp->route[i];
		string path = roads[routeIndex];
		out << path << ":" << temp->lineNum[i] << ": " 
			 << print_entire_line(temp->lineNum[i], path) << endl;
			 //print_entire_line(temp->lineNum[i], path)
	}
	
}

// print_entire_line()
// Prints entire line based on the given number line and the location of file
// Parameters: int line, string source
// Returns: string of the entire line from the text file
string Query::print_entire_line(int line, string source)
{
	ifstream file;
	file.open(source);
	if (!file.is_open())
	{
		return "line cannot be retrieved\n";
	}
	string temp;
	for(int i = 0; i < line; i++){
		getline(file, temp);
		if (i == line - 1){
			return temp;
		}
	}
	return "";
	file.close();
}

// changeOutput()
// Changes the output file 
// Parameters: string fileName
// Returns: None
void Query::changeOutput(string fileName)
{
	out.close();
	out.open(fileName);
	if (!out.is_open())
	{
		cout << "Could not open file\n";
	}
	return;
}