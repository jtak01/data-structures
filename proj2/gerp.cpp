// gerp.cpp
// driver file
// Jun Sung Tak

#include <iostream>
#include "Query.cpp"
#include <functional>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 3){
		cout << "usage: ./gerp input_directory output_directory\n";
		return 0;
	}
	Query q(argv[2]);
	q.setUp(argv[1]);
	q.run();
}
