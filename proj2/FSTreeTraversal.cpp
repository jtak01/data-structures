#include <iostream>
#include <string>
#include "FSTree.h"
#include "DirNode.h"

using namespace std;

void print(string r, DirNode *node);
void printCaller(string r);

int main(int argc, char* argv[])
{
	if (argc != 2)
		return 0;
	else 
	{
		printCaller(argv[1]);
	}
	return 0;
}

void printCaller(string r)
{
	FSTree a = FSTree(r);
	print(r, a.getRoot());
}

void print(string r, DirNode *node)
{
	for (int i = 0; i < node -> numSubDirs(); i++)
	{
		print(r + "/" + node -> getSubDir(i) -> getName(), 
			  node -> getSubDir(i));
	}
	for (int j = 0; j < node -> numFiles(); j++)
	{
		cout << r << "/" << node -> getFile(j) << endl;
	}
	cout << r << endl;
}