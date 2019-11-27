// NOTE: THIS UNIT TEST WAS COMPILED WITH THE "root" PRIVATE MEMBER VARIABLE
//       MOVED TO THE PUBLIC SECTION
//
// unit-test.cpp
// Comp15
// Spring 2019
// Unit test file for BinarySearchTree.cpp
// Written by: Jun Sung Tak
// Awknowledgements: Test value array "arr" was copied from the given 
//					 unit-test file
// Date: Feb 27, 2019

#include "BinarySearchTree.h"
#include "pretty_print.cpp"
#include <iostream>
using namespace std;

void test_remove(BinarySearchTree &tree);
void test_remove_extended(BinarySearchTree &tree);
void test_findMin(BinarySearchTree &tree);
void test_findMax(BinarySearchTree &tree);
void test_insert_and_contain(BinarySearchTree &tree);
void test_node_count(BinarySearchTree &tree);
void test_count_total(BinarySearchTree &tree);
void test_tree_height(BinarySearchTree &tree);

int MAX_LENGTH = 20;
int MAX_HEIGHT = 6;
int MIN_VALUE = -898;
int MAX_VALUE = 814;
int TOTAL_SUM = -1120;

int main()
{
	int arr[] = {258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255}; 
    BinarySearchTree tree;
    BinarySearchTree tree_backup;
    for (int i = 0; i < MAX_LENGTH; i++)
    {
    	tree.insert(arr[i]);
    }
    tree_backup = tree;
    cout << "tree was reset to original tree with assignement overload\n";
    test_findMin(tree);
    test_findMax(tree);
    test_remove(tree);
    tree = tree_backup;
    cout << "tree was reset to original tree with assignement overload\n";
    test_remove_extended(tree);
    tree = tree_backup;
    cout << "tree was reset to original tree with assignement overload\n";
    test_insert_and_contain(tree);
    tree = tree_backup;
    cout << "tree was reset to original tree with assignement overload\n";
    test_node_count(tree);
    tree = tree_backup;
    cout << "tree was reset to original tree with assignement overload\n";
    test_count_total(tree);
    tree = tree_backup;
    cout << "tree was reset to original tree with assignement overload\n";
    test_tree_height(tree);

}

// Test the tree_height function
// Prints lines to cout to indicate that the function being tested works
void test_tree_height(BinarySearchTree &tree)
{
	if (tree.tree_height() == MAX_HEIGHT)
		cout << "tree_height works on original tree\n";
	else 
		cout << "tree_height does NOT work on original tree\n";
	tree.insert(-521);
	if (tree.tree_height() == MAX_HEIGHT + 1)
		cout << "tree_height works on tree with its height changed\n";
	else 
		cout << "tree_height does NOT work as intended\n";
	tree.remove(-521); // Removes this element to get back to original tree
	tree.remove(-562); // After removing this element the height should be
					   // 1 less than the height for original tree
	if (tree.tree_height() == MAX_HEIGHT - 1)
		cout << "tree_height works on tree with its height decreased\n";
	else 
		cout << "tree_height does NOT work as intended\n";
	tree.remove(579);
	if (tree.tree_height() == MAX_HEIGHT - 1){
		cout << "tree_height works on tree when an element from a branch "
		     << "that is not the longest branch works\n";
	} else
		cout << "tree_height does NOT work as intended\n";
	BinarySearchTree t;
	if (t.tree_height() == -1)
		cout << "tree_height returns correct value when tree is empty\n";
	else
		cout << "tree_height returns incorrect value when tree is empty\n";
	t.insert(2); // Inserting random number to test if tree_height works  
				 // when there is one value in the BST
	if (t.tree_height() == 0){
		cout << "tree_height returns correct value of height of BST "
			 << "with one element\n";
	} else {
		cout << "tree_height returns incorrect value of height of BST "
			 << "with one element\n";
	}
}

// Test count_total function
// Prints lines to cout to indicate that the function being tested works
void test_count_total(BinarySearchTree &tree)
{
	if (tree.count_total() == TOTAL_SUM)
		cout << "count_total works on original tree\n";
	else 
		cout << "count_total does NOT work on original tree\n";
	tree.insert(579); //Now there are two 579, total sum should increase
					  //by 579
	if (tree.count_total() == TOTAL_SUM + 579)
		cout << "count_total works with duplicates\n";
	else 
		cout << "count_total does NOT work as intended\n";
	tree.remove(579);
	tree.insert(1000);
	if (tree.count_total() == TOTAL_SUM + 1000)
		cout << "count_total works when new element is inserted\n";
	else 
		cout << "count_total does NOT work as intended\n";
	BinarySearchTree t1;
	if (t1.count_total() == 0)
		cout << "count_total returns correct value when tree is empty\n";
	else 
		cout << "count_total returns incorrect value when tree is empty\n";
}

// Test node_count function
// Prints lines to cout to indicate that the function being tested works
void test_node_count(BinarySearchTree &tree)
{
	if (tree.node_count() == MAX_LENGTH)
		cout << "node_count works on original tree\n";
	else 
		cout << "node_count does NOT work on original tree\n";
	tree.insert(382); // This added value does not have to removed since 
					  // duplicates does not affect node_count's behavior
	if (tree.node_count() == MAX_LENGTH)
		cout << "node_count works when one of the nodes have a duplicate\n";
	else 
		cout << "node_count does NOT work as intended\n";
	tree.insert(431);
	if (tree.node_count() == MAX_LENGTH + 1)
		cout << "node_count works when a new element is inserted\n";
	else 
		cout << "node_count does NOT work as intended\n";
	tree.remove(431); // Removing the previously inserted element to test
	tree.remove(-3);
	if (tree.node_count() == MAX_LENGTH - 1)
		cout << "node_count works when an element is removed\n";
	else 
		cout << "node_count does not work as intended\n";
}

// Test insert and contains function
// Prints lines to cout to indicate that the function being tested works
void test_insert_and_contain(BinarySearchTree &tree)
{
	tree.insert(0);
	if (tree.contains(0) == true){
		cout << "Zero was inserted and contains work\n";
	}
	tree.insert(258); // 258 already exists in BST. This is the second one.
	if (tree.root -> count == 2)
		cout << "Inserting the same element works as intended\n";
	else 
		cout << "Inserting the same element does NOT work as intended\n";
	tree.insert(1000);
	if (tree.contains(1000))
		cout << "Inserting new element AND contains work\n";
	else 
		cout << "Inserting new element does not work\n";
	return;
}

// Test remove function
// Prints lines to cout to indicate that the function being tested works
void test_remove(BinarySearchTree &tree)
{
	tree.remove(258);
	if (tree.contains(258) == false and tree.root -> data == 382)
		cout << "Removing root works\n";
	else 
		cout << "Removing root does not work\n";
	tree.remove(-566);
	if (tree.root -> left -> data == -562)
		cout << "Removing node with two children works\n";
	else 
		cout << "Removing node with two children does NOT work\n";
	tree.remove(-898);
	if (tree.find_min() == -768)
		cout << "Removing node with no children works\n";
	else 
		cout << "Removing node with no children does NOT work\n";
	if (tree.remove(1000) == false)
		cout << "Removing a nonexistent value works\n";
	else 
		cout << "Removing a nonexistent value does not work\n";
	return;
}

// Further tests the remove function
// Prints lines to cout to indicate that the function being tested works
void test_remove_extended(BinarySearchTree &tree)
{
	tree.remove(382);
	if (tree.root -> right -> left -> data == 397)
		cout << "Removing a node with one child works\n";
	else 
		cout << "Removing a node with one child does NOT work\n";
	tree.insert(258);
	tree.remove(258);
	if (tree.contains(258)){
		cout << "Removing an element once which its count is greater than "
			 << "one works\n";
	} else {
		cout << "Removing an element once which its count is greater than "
			 << "one does NOT work\n";
	}
}

// Test find_min function
// Prints lines to cout to indicate that the function being tested works
void test_findMin(BinarySearchTree &tree)
{
	int min = tree.find_min();
	if (min == MIN_VALUE){
		tree.insert(-900);
		int min2 = tree.find_min();
		if (min2 == -900)
			cout << "find_min works so far\n";
		else 
			cout << "find_min does NOT work properly\n";
	}
	else
		cout << "find_min does NOT work properly\n";
	tree.remove(-900);
	BinarySearchTree tree1;
	tree1.insert(1);
	if (tree1.find_min() == 1){
		cout << "find_min works properly even if there is one "
			 << "element in the tree\n";
	} else {
		cout << "find_min does not work properly when there is "
		     << "one element in the tree\n";
	}
	return;
}

// Test find_max function
// Prints lines to cout to indicate that the function being tested works
void test_findMax(BinarySearchTree &tree)
{
	int max = tree.find_max();
	if (max == MAX_VALUE){
		tree.insert(900);
		int max2 = tree.find_max();
		if (max2 == 900)
			cout << "find_max works so far\n";
		else
			cout << "find_max does NOT work properly\n";
	}
	else
		cout << "find_max does NOT work properly\n";
	tree.remove(900);
	BinarySearchTree tree1;
	tree1.insert(1);
	if (tree1.find_min() == 1){
		cout << "find_max works properly even if there is one "
			 << "element in the tree\n";
	} else {
		cout << "find_max does not work properly when there is "
		     << "one element in the tree\n";
	}
	return;
}