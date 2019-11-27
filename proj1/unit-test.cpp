// unit-test.cpp
// Comp15 spring 2019
// 3/13/2019
// Jun Sung Tak
// Tests numerous functions for the trie data structure

// This unit test was run with all the functions and variables into 
// the public section in Dna.h file

#include "Dna.h"
#include <iostream>
using namespace std;

bool test_insert();
bool test_count();
bool test_remove();
bool test_removeAll();
bool test_preFixQ();
bool test_query();
bool test_calculateHelper();

int main()
{
	cout << "BEGIN UNIT TESTING FOR SEQMATCH\n";
	cout << endl;
	bool insert = test_insert();
 	bool count = test_count();
	bool remove = test_remove();
	bool removeAll = test_removeAll();
	bool prefix = test_preFixQ();
	bool query = test_query();
	cout << endl;
	if (insert and count and remove and removeAll and prefix and query)
		cout << "All functions working properly, end of test.\n";
	else 
		cout << "Not all functions work, check again.\n";
}

// Tests the insert function
// Tests by comparing invidual node's 'data' variable
bool test_insert()
{
	cout << "TESTING INSERT //////////////////////////\n";
	Dna a;
	a.insert_caller("GGT");
	a.insert_caller("ACGTATT");
	a.insert_caller("AGTGAC");
	a.insert_caller("TGAT");
	if (a.root -> child[2] -> data != 'G')
		return false;
	if (a.root -> child[3] -> child[2] -> child[0] -> data != 'A')
		return false;
	cout << "Testing insert complete, no errors\n";
	return true; 
}

// Test nodeCount function
// Tests by comparing node counts after insertion and removal
bool test_count()
{
	cout << "TESTING COUNT //////////////////////////\n";
	Dna a;
	a.insert_caller("AGT");
	a.insert_caller("CCGTATT");
	a.insert_caller("AGTGAC");
	if (a.nodeCount(a.root) != 14)
		return false;
	a.remove_caller("AGT");
	if (a.nodeCount(a.root) != 14)
		return false;
	cout << "Testing count complete, no errors\n";
	return true;
}

// Test remove function
// Test by removing and then seeing if those sequences are still in the trie
bool test_remove()
{
	cout << "TESTING REMOVE //////////////////////////\n";
	Dna a;
	a.insert_caller("AA");
	a.insert_caller("AAA");
	a.insert_caller("GTCAA");
	a.insert_caller("CGTACCGT");
	a.remove_caller("AAA");
	a.remove_caller("GTCAA");
	if (a.contains("AAA", a.root))
		return false;
	if (a.contains("GTCAA", a.root))
		return false;
	cout << "Testing remove complete, no errors\n";
	return true;
}

// Tests deleteAll function
// Tests by making sure that nodeCount is 0 after the function deletes
// everything
bool test_removeAll()
{
	cout << "TESTING REMOVING ALL //////////////////////////\n";
	Dna a;
	a.insert_caller("AA");
	a.insert_caller("AAA");
	a.insert_caller("GTCAA");
	a.insert_caller("CGTACCGT");
	a.insert_caller("TTTGACGA");
	a.insert_caller("CCGTAT");
	a.insert_caller("GGTAATCGT");
	a.deleteAll(a.root);
	if (a.nodeCount(a.root) != 0)
		return false;
	cout << "Testing removing all complete, no errors\n";
	return true;
}

// Test preFixQ function
// Tests by the function's return value
// If preFixQ works properly it should return true
bool test_preFixQ()
{
	cout << "TESTING PREFIX QUERY//////////////////////////\n";
	Dna a;
	a.insert_caller("AA");
	a.insert_caller("AAA");
	a.insert_caller("TGGTCA");
	a.insert_caller("AATCGCGT");
	a.insert_caller("AAAGCGAT");
	a.insert_caller("CGTAGTCAGTA");
	a.insert_caller("AAAA");
	a.insert_caller("GTCAA");
	a.insert_caller("CGTACCGT");
	a.insert_caller("CGTAGTATCGAGA");
	a.insert_caller("TTTGACGA");
	a.insert_caller("CGTAGTGTAGC");
	a.insert_caller("CCGTAT");
	a.insert_caller("GGTAATCGT");
	char prefix[500];
	if (!a.preFixQ("CGTAGT", a.root, prefix, 6, "CGTAGT"))
		return false;
	if (!a.preFixQ("AAA", a.root, prefix, 3, "AAA"))
		return false;
	if (a.preFixQ("AT", a.root, prefix, 2, "AT"))
		return false;
	cout << "Testing preFix query all complete, no errors\n";
	return true;
}

// Tests query function
// This test tests helper functions that query calls
// If those helper functions work as intended then the function must also 
// work since it utilizes the return values of the helper function
bool test_query()
{
	cout << "TESTING QUERY////////////////////\n";
	Dna a;
	a.insert_caller("AA");
	a.insert_caller("AAA");
	a.insert_caller("CGCGTAA");
	a.insert_caller("AA");
	a.insert_caller("AAA");
	a.insert_caller("AAACGT");
	a.insert_caller("ACGCAT");
	a.insert_caller("ACGCT");
	a.insert_caller("CCTA");
	cout << "Testing individual helper functions for query\n";
	if (a.calculateHelper("GTAGACA", "GTACGA") != 3)
		return false;
	if (a.calculateHelper("AGATCA", "ATGACA") != 1)
		return false;
	if (a.calculatePercent(4, "AGTAC", "AGTC") != 60)
		return false;
	if (a.calculatePercent(7, "GATC", "GATGGAA") != 43)
		return false;
	cout << "Testing query all complete, no errors\n";
	return true;
}
