#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctype.h>
#include <vector>


using namespace std;

// TA: Clara 
const std::string NAME = "text.txt";

using namespace std;

void process(string);
bool exists(string word, vector<string> &arr);
string processString(string);

int main()
{
	// bool run = true;
	// string a;
	// while (run == true)
	// {
	// 	cin >> a;
	// 	if (a == "quit")
	// 		return 0;
	// 	process(a);
	// 	cout << endl;
	// }
	string a = "jacket. It was a blue jacket with brass buttons, quite new.";
	string b = "jacket. a the hi jacket with mate";
	string c = "the the the the the. .the the";
	stringstream ss(c);
	string word;
	vector<string> duplicate;
		while(!ss.eof())
		{
			ss >> word;
			word = processString(word);
			if (!exists(word, duplicate)){
				duplicate.push_back(word);
			}
		}
	for (int i = 0; i < duplicate.size(); i++)
		cout << duplicate[i] << endl;
}

void process(string word)
{
	if (word == ""){
		cout << endl;
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

	cout << word.substr(startIndex, lengthOfString) << endl;
}

string processString(string word)
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
	//cout << startIndex << endl;
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

// void read()
// {
// 	ifstream data;
// 	data.open(NAME);
// 	//cout << fileName << " in " << route << endl;
// 	if (!data.is_open()){
// 		cout << "Could not build index, exiting.\n";
// 		exit(0);
// 	}
// 	string temp;
// 	int counter = 0;
// 	while (!data.eof())
// 	{
// 		data >> temp;
// 		counter++;
// 		cout << "Position at: " << data.tellg() << endl;
// 		cout << temp << endl;
// 	}
// 	cout << "inputted " << counter << " times.\n";
// 	data.close();
// }.

bool exists(string word, vector<string> &arr)
{
	int length = arr.size();
	for(int i = 0; i < length; i++)
	{
		if(arr[i] == word)
			return true;
	}
	return false;
}