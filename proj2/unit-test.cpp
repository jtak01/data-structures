// unit-test.cpp
// Tests for duplicate removing algorithm
// Jun Sung Tak
// Other functionalities were tested with the provided with
// gerpdiff. The query requests that was tested with is in 
// "testinput.txt"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void test_duplicate();
bool exists(string, vector<string> &);
string processString(string word);

int main()
{
	test_duplicate();
}

// This functions tests the exists function and
// makes sure that the way to remove duplicate is 
// correct
void test_duplicate()
{
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
	for (int i = 0; i < int(duplicate.size()); i++)
		cout << duplicate[i] << endl;
	cout << "No duplicates inside the vector. There should only"
		 << " one the.\n";
}

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