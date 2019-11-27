// Node.h
// Node struct for hashtable
// Jun Sung Tak

#include <vector>

#ifndef NODE_H_
#define NODE_H_


struct Node
{
    std::vector<std::string> info;
    std::vector<int> lineNum;
    std::vector<int> route;
    Node *next;
};

#endif