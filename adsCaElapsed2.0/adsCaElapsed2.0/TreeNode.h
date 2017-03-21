#ifndef TREENODE_H
#define TREENODE_H
#include <iostream>
#include <map>
#include <string>
#include "City.h"
using namespace std;

class TreeNode
{
	friend class BST;
	friend class City;
public:
	TreeNode();
	TreeNode(City); //node constructor
	bool isLeaf();
	City city;
	TreeNode * left; //left child
	TreeNode * right;//right child
};
#endif