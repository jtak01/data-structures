#include <iostream>
#include "LinkedList.h"

  
using namespace std;

#ifndef ACTOR_H_
#define ACTOR_H_

class Actor 
{
	public:
		Actor();
		Actor(string);
		~Actor();
		void insert_movie(string name);
		bool in_movie(string movie);
		string connect(Actor a);
		friend bool operator==(Actor const& a1, Actor const& a2);
		friend bool operator!=(Actor const& a1, Actor const& a2);
		friend ostream& operator <<(ostream& out, const Actor &);
		LinkedList<string> movies;
	private: 
		string name;
		
};

#endif