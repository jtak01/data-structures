#include <iostream>
#include "Actor.h"
#include "LinkedList.cpp"
#include <string>
#include <bits/stdc++.h>

using namespace std;


Actor::Actor()
{
	name = "";
}

Actor::Actor(string actor)
{
	name = actor;
}

Actor::~Actor()
{
	name = "";
}

//template<class LinkedList>
void Actor::insert_movie(string name)
{
	bool a;
	movies.find(name, a);
	if (!a)
	{
		movies.insert(name);
	}
	return;
}

//template<class LinkedList>
bool Actor::in_movie(string movie)
{
	bool a = false;
	movies.find(movie, a);
	if (a == true)
		return true;
	else
		return false;
}

string Actor::connect(Actor a)
{
	vector<string> movie_list;
	string final_word = "";
	int length = movies.get_length();
	for (int i = 0; i < length; i++)
		movie_list.push_back(movies.get_value_at(i));
	int length2 = a.movies.get_length();
	for (int k = 0; k < length2; k++)
		movie_list.push_back(a.movies.get_value_at(k));
	sort(movie_list.begin(), movie_list.end());
	int final_length = length + length2;
	for (int j = 0; j < final_length - 1; j++)
	{
		if (movie_list[j] == movie_list[j + 1])
			final_word = movie_list[j];
	}
	return final_word;
}

bool operator== (Actor const& a1, Actor const& a2)
{
	return a1.name == a2.name;
}

bool operator!= (Actor const& a1, Actor const& a2)
{
	return a1.name != a2.name;
}

ostream & operator <<(ostream& out, const Actor & a)
{
	out << a.name;
	return out;
}
