// BinarySearchTree.cpp
// Comp15
// Spring 2019
// Implementation of BinarySearchTree.h 
// This class has functions for implementing a BST (Binary Search Tree)
// Written by: Jun Sung Tak
// Date: Feb 27, 2019

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;

// Constructor
BinarySearchTree::BinarySearchTree()
{
        // TODO: Students write code here
        root = NULL;
}

// Destructor
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = NULL;
}

// Input: Pointer to a node
// Returns: Nothing
// Does: Deletes all nodes in the tree
void BinarySearchTree::post_order_delete(Node *node)
{
    if (node == NULL)
        return;
    if (node -> left != NULL)
        post_order_delete(node -> left);
    if (node -> right != NULL)
        post_order_delete(node -> right);
    delete node;
    return;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        root = pre_order_copy(source.root);
}
     
// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    if (this != &source)
    {
        post_order_delete(this -> root);
        this -> root = pre_order_copy(source.root);
    }
    return *this;
}

// Input: Pointer to a node
// Returns: Pointer to a node
// Does: Copies a tree to a new node and returns that node
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        if (node == NULL)
                return NULL;
        Node *new_node = new Node();
        new_node -> data = node -> data;
        new_node -> count = node -> count;
        new_node -> left = pre_order_copy(node -> left);
        new_node -> right = pre_order_copy(node -> right);
        return new_node;
}

// Input: Nothing
// Returns: Integer value of the smallest number of the BST
// Does: Returns the integer value of the smallest number of BST, actual
//       functionality is done by the private helper function
int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

// Input: Pointer to a node
// Returns: Pointer to the node containing the smallest element in the BST
// Does: Traverses the BST until it is on the left most node and returns 
//       that node
Node *BinarySearchTree::find_min(Node *node) const
{
    if (node -> left == NULL)
        return node;
    else 
        return find_min(node -> left);
}

// Input: Nothing
// Returns: Integer value of the largest number of the BST
// Does: Returns the integer value of the largest number of BST, actual
//       functionality is done by the private helper function
int BinarySearchTree::find_max() const
{
    if (root == NULL)
        return INT_MAX;
    return find_max(root)->data;

}

// Input: Pointer to a node
// Returns: Pointer to the node containing the largest element in the BST
// Does: Traverses the BST until it is on the right most node and returns 
//       that node
Node *BinarySearchTree::find_max(Node *node) const
{
        // TODO: Students write code here
    Node *curr = node;
    if (curr -> right == NULL)
        return curr;
    else 
        return find_max(curr -> right);
}

// Input: Int value to search for
// Returns: Boolean of whether or not the given value is in the BST
// Does: Determines whether the given value is in the BST. Calls private
//       helper function to search for the value
bool BinarySearchTree::contains(int value) const
{
    if (root == NULL)
        return false;
    return contains(root, value);
}

// Input: Pointer to a node and int value to search for
// Returns: Boolean of whether or not the given value is in the BST
// Does: Traverses the BST until the value it was looking for is found
//       when found, returns true and when it is not found returns false
bool BinarySearchTree::contains(Node *node, int value) const
{
        // TODO: Students write code here
    if (node -> data > value and node -> left != NULL)
        return contains(node -> left, value);
    if (node -> data < value and node -> right != NULL)
        return contains(node -> right, value);
    if (node -> data == value)
        return true;
    return false;
}

// Input: Int value to insert
// Returns: Nothing
// Does: Calls private helper function 
void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

// Input: Pointer to a node, pointer to a node that is the parent of the 
//        first node that was given, and the value to insert
// Returns: Nothing
// Does: Inserts the given value in the approporiate place in the BST
//       if the value is already in the BST, then that value's multiplicity,
//       the 'count' variable in this case is incremented
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{
        // TODO: Students write code here
    if (root == NULL){
        root = newNode(value);
        return;
    }
    if (node == NULL and value > parent -> data){ 
            parent -> right = newNode(value);
            return;
    } 
    if (node == NULL and value < parent -> data) {
            parent -> left = newNode(value);
            return;
    }
    parent = node;
    if (value > parent -> data){
        insert(node -> right, parent, value);
    }  else if (value < parent -> data) {
        insert(node -> left, parent, value);
    } else if (value == parent -> data){
        node -> count++;
    }
    return;
}

// Input: Int value to remove
// Returns: Boolean value of whether the int value has been removed
// Does: Calls private helper function
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}

// Input: Pointer to a node, pointer to a node that is the parent of the 
//        first node that was given, and the value to remove
// Returns: Boolean value of whether the int value has been removed
// Does: Traverses and finds the given value, then removes it. If the 
//       'count' variable of the node that contains the int value is larger
//        than 1, then the 'count' variable is decremented
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
    if (node == NULL)
        return false;
    if (node -> data < value)
        return remove(node -> right, node, value);
    else if (node -> data > value)
        return remove(node -> left, node, value);
    else if (node -> data == value){
        if (node -> count > 1){ // If node's count is greather than 1
            node -> count--;
            return true;
        } else if (node -> left == NULL and node -> right == NULL){ 
            if (node == parent -> right) // When the node to delete has no                  
                find_parent(parent, node) -> right = NULL; // children
            else 
                find_parent(parent, node) -> left = NULL;
            return remove_helper(node);
        } else if (node -> right == NULL){ // When there is only left node
            if (node -> left -> data > parent -> data){
                parent -> right = node -> left;
                return remove_helper(node);
            }
            parent -> left = node -> left;
            return remove_helper(node);
        } else if (node -> left == NULL){ // When there is only right node
            if (node -> right -> data < parent -> data){
                parent -> left = node -> right;
                return remove_helper(node);
            }
            parent -> right = node -> right;
            return remove_helper(node);
        } else { // When there are both left and right node
            Node *temp = find_min(node -> right);
            node -> data = temp -> data;
            node -> count = temp -> count;
            return remove(node -> right, node, temp -> data);
        }
    }
    return false;
}

// Input: Pointer to a node that is to be removed
// Returns: Boolean true since when this function is called, the value is
//          for sure able to be removed
// Does: Deletion of the node
bool BinarySearchTree::remove_helper(Node *node)
{
    node -> data = 0;
    node -> count = 0;
    delete node;
    node = NULL;
    return true;
}

// Input: None
// Returns: Int of the tree height
// Does: Calls private helper function
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

// Input: Pointer to a node
// Returns: Int of the tree height
// Does: Traverses the BST and gets the height for left and right subtree
//       returns the larger value of the two
int BinarySearchTree::tree_height(Node *node) const
{
    if (node == NULL)
        return -1;
    int right = tree_height(node -> right);
    int left = tree_height(node -> left);
    if (right > left)
        return right + 1;
    else
        return left + 1;
}

// Input: None
// Returns: Int of number of individual nodes in the BST
// Does: Calls private helper function
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

// Input: Pointer to a node
// Returns: Int of number of individual nodes in the BST
// Does: Tranverses the BST and whenever node accesses its children adds 1
//       to the number of nodes
int BinarySearchTree::node_count(Node *node) const
{
        // TODO: Students write code here
    int counter = 0;
    if (node == NULL)
        return counter;
    counter = 1;
    if (node -> left != NULL){
        counter = counter + node_count(node -> left);
    }
    if (node -> right != NULL){
        counter = counter + node_count(node -> right);
    }
    return counter;
}
// Input: None
// Returns: int of the sum of all the node values (including duplicates)
// Does: Calls private helper function
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

// Input: None
// Returns: Int of the sum of all the node values (including duplicates)
// Does: Traverses the BST and adds up the value multiplied by 'count'.
int BinarySearchTree::count_total(Node *node) const
{
    if (node == NULL)
        return 0;
    return node -> data * node -> count + 
           count_total(node -> left) + count_total(node -> right);
}

// use the printPretty helper to make the tree look nice
// This function was given
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}

// Helper function to locate parent node of a given node
// This function was given
Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

// Input: Int value
// Returns: Pointer to a new node
// Does: Initializes the node struct with 'data = value'. All other values
//       are set to their default states
Node* BinarySearchTree::newNode(int value){
    Node *temp = new Node;
    temp -> data = value;
    temp -> count = 1;
    temp -> left = NULL;
    temp -> right = NULL;
    return temp;
}
