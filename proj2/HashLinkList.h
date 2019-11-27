// HashLinkList.h
// Most of this class was taken from LinkedList.h from
// a previous assignment

#include "Node.h"

using namespace std;

#ifndef HASH_LINK_LIST_H
#define HASH_LINK_LIST_H

class HashLinkList
{
public:
	HashLinkList();
	~HashLinkList();
	void insert(string, int, int);
	void insert_by_node(Node *node);
	void print(ostream &);
	int get_length();
	bool is_empty();
	Node* find_node(string, bool &) const; // Didnt test this 
										   // function but it looks right
	Node* get_value_at(int);
	void burn_link();

private:
	Node *head;
};

#endif