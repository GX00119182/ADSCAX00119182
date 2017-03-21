
#include <iostream>
#include <map>
#include <string>
#include "City.h"
#include "TreeNode.h"
using namespace std;

TreeNode::TreeNode()
{
	left = NULL;
	right = NULL;
}

TreeNode::TreeNode(City c)
{
	city = c;

}

bool TreeNode::isLeaf() {
	if (left == NULL &&right == NULL) {
		return true;
	}
	else {
		return false;
	}
}