#include <iostream>
#include <fstream>
#include "SixDegree.h"

using namespace std;

SixDegree::SixDegree()
{
	int size = get_num();
	p.initialize_graph(size);
	return;
}

void SixDegree::populate_graph()
{
	ifstream data;
	data.open("actors.txt");
	if (!data.is_open()){
		cout << "actors.txt cannot be open\n";
		exit(0);
	}
	string temp;
	while(!data.eof())
	{
		getline(data, temp);
		Actor a(temp);
		while(temp != "*" and temp != "")
		{
			getline(data, temp);
		 	if (temp != "*"){
		 		a.insert_movie(temp);
				//cout << temp << endl;
		 	}
		}
		p.add_vertex(a);
	}
	data.close();
	int size = get_num();
	for (int i = 0; i < size; i++){
		for (int j = 0; j < size; j++){
			if (p.get_vertex(i) != p.get_vertex(j)){
				string common = p.get_vertex(i).connect(p.get_vertex(j));
				if (common != "")
					p.add_edge(p.get_vertex(i), p.get_vertex(j), common);
			}
		}
	}
}

void SixDegree::BFS(Actor start, Actor end, ostream &out)
{
	p.clear_marks();
	p.initialize_path();
	bool temp = false;
	Queue<Actor> top;
	Queue<Actor> bot;
	Actor curr;
	top.enqueue(start);
	do
	{
		if (start == end)
			temp = true;
		else 
		{
			top.dequeue(curr);
			p.mark_vertex(curr);
			p.get_to_vertices(curr, bot);
			while (!bot.is_empty())
			{
				Actor a;
				bot.dequeue(a);
				if (!p.is_marked(a))
				{
					top.enqueue(a);
					p.update_predecessor(curr, a);
				}
				if (a == end){
					temp = true;
					break;
				}
			}
		}
	}
	while (temp == false);
	p.report_path(out, start, end);
}

int SixDegree::get_num()
{
	int num = 1;
	ifstream data;
	data.open("actors.txt");
	if (!data.is_open()){
		cout << "actors.txt cannot be open\n";
		exit(0);
	}
	string temp;
	while (!data.eof()){
		getline(data, temp);
		if (temp == "*")
			num++;
	}
	return num - 1;
}