/*
 *      CircularSequence.cpp 
 *      PartyPlaylist 
 *      Comp 15 Lab 3
 *
 *      2016-09-16 Created by Yennie Jun
 *      2016-09-20 Documentation added by Mark A. Sheldon, Tufts University
 */

#include <iostream>
#include <stdexcept>

#include "CircularSequence.h"


using namespace std;


/*
 * Return the index of the next element in the sequence.
 * Wraps around!
 */
int CircularSequence::nextIndex(int index)
{
        return (index + 1) % capacity;
}


/* Default Constructor */
CircularSequence::CircularSequence()
{
        init(INIT_CAPACITY);
}

/* 
 * Overloaded Constructor for a sequence with a hint for an initial
 * capacity. 
 */
CircularSequence::CircularSequence(int initialCapacity)
{
        init(initialCapacity);
}

/*
 * Initialize a new, empty sequence with an initial capacity.
 */
void CircularSequence::init(int initialCapacity)
{
        capacity      = initialCapacity;
        sequenceArray = new ElementType[capacity];
        currentSize   = 0;
        front         = 0;
        back          = 0;
}

/*
 * Destructor:  recycles the dynamically allocated array containing
 * the data.
 */
CircularSequence::~CircularSequence()
{
        delete [] sequenceArray;
}

/* 
 *  Add given element to the back of the list 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtBack(ElementType elem) 
{
        if (currentSize == capacity) {
                expand();
        }
        sequenceArray[back] = elem;
        back                = nextIndex(back);
        currentSize++;

        return true;
}

/* 
 *  Add given element to the front of the list 
 *  Return true if element is successfully added.
 */
bool CircularSequence::addAtFront(ElementType elem)
{
        if (currentSize == capacity)
            expand();
        if (front == 0)
        {
            sequenceArray[capacity - 1] = elem;
            front = capacity - 1;
        } else {
            sequenceArray[front - 1] = elem;
            front++;
        }
        currentSize++;
        return true; 
}
                
/*
 * Remove the element at the back of the list 
 * and return it.
 */
ElementType CircularSequence::removeFromBack() 
{
        ElementType a;
        if (back == 0){
            back = capacity - 1;
            a = sequenceArray[back];
        } else {
            a = sequenceArray[back - 1];
            back--;
        }
        return a;
}
 
/*
 * Remove the element at the front of the list 
 * and return it.
 */
ElementType CircularSequence::removeFromFront()
{
        ElementType a;
        if (front == capacity - 1)
        {
            a = sequenceArray[front];
            front = 0;
        } else {
            a = sequenceArray[front];
            front++;
        }
        return a;
}

/*
 * Expand the capacity of the array by a factor of 2.
 */
void CircularSequence::expand() 
{
        int nsize = capacity * 2;
        ElementType *narray = new ElementType[nsize];
        for (int i = 0; i < currentSize; i++)
        {
            narray[i] = sequenceArray[i];
        }
        delete [] sequenceArray;
        sequenceArray = narray;
        capacity = nsize;

}

/*
 * Print the contents of the sequence, one element per line.
 */
void CircularSequence::printSequence() 
{
        int currIndex = front;
        for (int i = 0; i < currentSize; i++) {
                cout << sequenceArray[currIndex] << endl;
                currIndex = nextIndex(currIndex);
        }
}
