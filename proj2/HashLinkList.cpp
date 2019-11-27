// HashLinkList.cpp
// Implementation of HashLinkList.h
// Deals with chaining of the hashtable
// Modified by: Jun Sung Tak
// NOTE: This class was mostly taken from LinkedList.cpp which was given to 
// us in a previous assignment. It was re-written to better suit this 
// assignement

#include <iostream>
#include <algorithm>
#include "HashLinkList.h"

using namespace std;

// Constructor
HashLinkList::HashLinkList()
{
	head = NULL;
}

// Destructor
HashLinkList::~HashLinkList()
{
	Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
    head = NULL;
}

// insert()
// Inserts the given word into the index of the hashtable
// Parameters: string word, int line, int path
// Returns: None
void HashLinkList::insert(string word, int line, int path)
{
	Node *temp = new Node;
    temp->info.push_back(word);
    temp->next = head;
    temp->lineNum.push_back(line); 
    temp->route.push_back(path);
    head = temp;
    return;
}

// insert_by_node()
// Inserts entries by given a node into the linked list
// Parameters: Node *node
// Returns: None 
void HashLinkList::insert_by_node(Node *node)
{
    node->next = head;
    head = node;
}

// print()
// prints the entire linked list
// Used for testing purposes
// Parameters: ostream &out
// Returns: None
void HashLinkList::print(ostream &out) 
{
	Node *temp = head;
    while (temp != NULL)
    {
        int size = temp->info.size();
        for(int i = 0; i < size; i++){
            out << temp->route[i] << ":" << temp->lineNum[i] << ": " 
                << temp->info[i] << endl;
        }
        temp = temp->next;
    }
}

// get_length()
// Determines the length of the linked list
// Parameters: None
// Returns: None
int HashLinkList::get_length()
{
	Node *current = head;
    int count = 0;
    while (current != NULL) 
    {
        count++;
        current = current->next;
    }
    return count;
}

// is_empty()
// Determines of the linked list is empty
// Mostly used for testing purposes
// Parameters: None
// Returns: Boolean of whether the linked list is empty of not
bool HashLinkList::is_empty()
{
	return (head == NULL);
}

// get_value_at()
// Gets the node at index of the linked list
// Parameters: int index
// Returns: Node at the value of the index of linked list
Node* HashLinkList::get_value_at(int index)
{
	if (is_empty())
        return NULL;
    Node *current = head;
    int current_index = 0;

    while ((current_index < index) && (current != NULL)) 
    {
        current = current->next;
        current_index++;
    }
    return current;
}

// find_node()
// Searches for the node in the linked list. &found is turned to true if 
// the node with the word is found
// Parameters: string word, bool &found 
// Returns: Node
Node* HashLinkList::find_node(string word, bool &found) const
{
    bool more_to_search;
    Node *node;

    node = head;
    found = false;
    more_to_search = (node != NULL);

    while (more_to_search && !found)
    {
        string nodeWord = node->info[0];
        transform(nodeWord.begin(), nodeWord.end(), nodeWord.begin(),::tolower);
        if (word == nodeWord)
        {
            found = true;
            break;
        }
        node = node->next;
        more_to_search = (node != NULL);
    }
    return node;
}

// burn_link()
// Properly deallocates memory for linked list
// Parameters: None
// Returns: None
void HashLinkList::burn_link()
{
	Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}