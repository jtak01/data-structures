// Name: Jun Sung Tak 
// Date: 22nd Jan 
// Assignment: Lab1
// Course Number: 15

#include "ArrayList.h"
#include "Pirate.h"

using namespace std;

int main()
{
//        Pirate a("Jack");
//        Pirate b("Jim");
//        Pirate c("Jill");
//        Pirate d("Jenny");
//        Pirate e("Jon");

        ArrayList list;

//        list.insert_pirate(a);
//        list.insert_pirate(b);
//        list.insert_pirate(c);
//        list.insert_pirate(d);
//        list.insert_pirate(e);

        ifstream inFile;
        inFile.open("pirate_names.txt");

        for (int i = 0; i < 200; i++)
        {
                Pirate arb;
                arb.generate_pirate_name(inFile, 100);
                arb.assign_pirate_id();
                list.insert_pirate(arb);
        }
        list.print();
}
