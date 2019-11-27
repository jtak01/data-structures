/*  
 * LinkedList.cpp 
 * COMP15 hw2   
 * Spring 2019
 * Jun Sung Tak
 * 4/Feburary/2019
 * Implementation for Linked List of Green Line Extension Stations
 */

#include "LinkedList.h"
#include <iostream>
using namespace std;

// Default constructor
LinkedList::LinkedList(){
    length = 0;
    head = NULL;
    currPos = NULL;
}

// Destructor
LinkedList::~LinkedList() {
    if (head == NULL)
        delete head;
    NodeType *curr = head;
    NodeType *temp;
    while (curr != NULL)
    {
        temp = curr -> next;
        delete curr;
        curr = temp;
    }
    delete currPos;
    length = 0;
}

// Assignment operator
LinkedList & LinkedList::operator = (const LinkedList &l){
    NodeType *temp;
    while (head != NULL){
        temp = head;
        head = head->next;
        delete temp;
    }
    length = l.length;
    currPos = NULL;
    if (l.head == NULL)
        head = NULL;
    else{
        head = new NodeType;
        head->info = l.head->info;
        head->next = NULL;
        NodeType *curr = head;
        NodeType *orig = l.head;
        while (orig->next != NULL){
            curr->next = new NodeType;
            curr->next->info = orig->next->info;
            curr->next->next = NULL;
            orig = orig->next;
            curr = curr->next;
        }
    }
    return *this;
}

// Input: nothing
// Returns: the length
// Does: returns the length of the LL
int LinkedList::getLength() const{
    return length;
}

// Input: nothing
// Returns: true if currPos is NULL
// Does: determines if currPos is NULL or not
bool LinkedList::isCurrPosNull() const{
    return currPos == NULL;    
}

// Input: Station
// Returns: Nothing
// Does: Inserts the given station into a linked list
void LinkedList::insertStation(Station s){
    NodeType *temp = new NodeType;
    temp -> info = s;
    temp -> next = head;
    head = temp;
    length++;
    return;
}

// Input: Station
// Returns: Nothing
// Does: Removes the given station if it is in the list already
void LinkedList::removeStation(Station s){
    if (head -> info.isEqual(s))
    {
        NodeType *temp = head;
        head = temp -> next;
        delete temp;
        return;
    }
    NodeType *curr = head -> next;
    NodeType *prev = head;
    while (curr != NULL)
    {
        if (curr ->info.isEqual(s))
        {
            //Remove the station
            prev -> next = curr -> next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr -> next;
    }
}

// Input: None 
// Returns: Station
// Does: Returns the next station in the list
Station LinkedList::getNextStation(){
    NodeType *lastStation = NULL;
    if (currPos == NULL){
        return head -> info;
    } else if (currPos -> next == NULL){
        lastStation = currPos;
        resetCurrPos();
    } else {
        NodeType *station = currPos;
        currPos = currPos -> next;
        return station -> info;
    }
    return lastStation -> info;
}

// Input: None
// Returns: None
// Does: Resets the member variable, currPos, to NULL
void LinkedList::resetCurrPos(){
   currPos = NULL;
}

// Input: None
// Returns: None
// Does: Empties the linked list
void LinkedList::makeEmpty(){
    NodeType *curr = head;
    while (curr != NULL)
    {
        curr = curr -> next;
        delete head;
        head = curr;
    }
}

// Input: ostream 
// Returns: None
// Does: Prints to the given ostream object 'out'
void LinkedList::print(ostream &out){
    if (head == NULL){
        return;
    }
    NodeType *curr = head;
    while (curr != NULL){
        curr -> info.print(out);
        if (curr -> next == NULL){
            out << " " << calculateDistance(curr -> info) << endl;
            return;
        }
        out << " " << calculateDistance(curr -> info) << " == ";
        curr = curr -> next;
    }
}

// Input: Station
// Returns: Distance of the given station to the last station
// Does: Calculates the number of stations between the given station and 
//       the last station
int LinkedList::calculateDistance(Station s){
    NodeType *temp = head;
    int counter = 0;
    while (temp != NULL)
    {
        if (temp -> info.isEqual(s))
            break;
        temp = temp -> next;
    }
    while (temp != NULL)
    {
        temp = temp -> next;
        counter++;
    }
    return counter - 1;
}






