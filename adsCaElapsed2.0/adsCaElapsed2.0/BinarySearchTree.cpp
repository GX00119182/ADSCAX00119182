#include <iostream>
#include <map>
#include <string>
#include "City.h"
#include "TreeNode.h"
using namespace std;


class BST {
	//friend class TreeNode;

public:
	BST();
	~BST();
	void insert(string name, double lon, double lat);//insert by name, create new obj of city
	void deleteCity(string name);//delete by name
	//void deleteNode(TreeNode *node);
							//missing search method
	void display();
	bool isEmpty();
	int height();
	

private:
	TreeNode * root;
	void insertPrivate(TreeNode *newNode, TreeNode *curr);//private insert method to allow for recursion
	void displayPrivate(TreeNode *newNode);
	TreeNode* findSmallestPrivate(TreeNode *newNode);
	void deleteCityPrivate(string name, TreeNode *node);//delete city method allowing access to root
	void Remove(TreeNode *&nodeToDel);
};

BST::BST()
{
	root = NULL;
}

BST::~BST()
{
	delete root; //recursively deletes all nodes below the root as well as itself
}

bool BST::isEmpty() 
{
	if (root == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//---------------------------INSERTION----------------------------------------------------
/* 
*usage: based on/modified
*author:Alex Allain
*Url: http://www.cprogramming.com/tutorial/lesson18.html
*Date:14/3/17
*Used this site to get my head around recursive insert method(s).
*/
void BST::insert(string name, double lon, double lat)
{
	TreeNode *temp = new TreeNode;
	temp->city = City(name, lon, lat);
	temp->left = NULL;
	temp->right = NULL;
	if (!isEmpty()) //if tree != null, then search for last node and insert at available position 
	{
		insertPrivate(temp, root);
	}
	else //if its empty, set new node to be the root node
	{
		root = temp;
	}
}

void BST::insertPrivate(TreeNode *newNode, TreeNode *curr)
{
	if (newNode->city < curr->city) //if less go left
	{
		if (curr->left != NULL)//checks current nodes for leaf nodes
		{
			insertPrivate(newNode, curr->left);
		}
		else
		{
			curr->left = newNode;
		}
	}
	else { //if more or equal go right
		if (curr->right != NULL) {
			insertPrivate(newNode, curr->right); //checks current nodes for leaf nodes
		}
		else {
			curr->right = newNode;
		}
	}
}
//-----------------------------DELETION--------------------------------------------------------

TreeNode* BST::findSmallestPrivate(TreeNode *node)
{
	if (isEmpty())
	{
		cout << "tree is empty" << endl;

	}
	else
	{
		if (node->left == NULL)
		{//no need to look at right as will always be greater than parent
			return node;
		}
		else
		{
			return findSmallestPrivate(node);
		}
	}

}

void BST::deleteCity(string n)
{
	if (!isEmpty())
	{
		deleteCityPrivate(n, root);
	}
}

void BST::deleteCityPrivate(string n, TreeNode *parent)
{//tutorial 10

		if (n < parent->city.getName())
		{
			if (parent->left != NULL)
			{
				deleteCityPrivate(n, parent->left);
			}
			else
			{
				cout << n << " not in tree" << endl;
			}
		}
		else if (n > parent->city.getName())
		{
			if (parent->right != NULL)
			{
				deleteCityPrivate(n, parent->right);
			}
			else
			{
				cout << n << " not in tree" << endl;
			}
		}
		else
		{
			Remove(parent);
		}
	
}

void BST::Remove(TreeNode *&node)
{
	
		TreeNode* temp = new TreeNode;
		TreeNode* smallestRight; //used delete the smallest node

		 if (node->right == NULL) //if one child left
		{
			temp = node;
			node = node->left;
			delete temp;
		}

		 //if 1 child right
		 if (node->left == NULL)
		 {
			 temp = node;
			 node = node->right;
			 delete temp;
		 }

		/*
		else if (node->left == NULL && node->right != NULL)
		{
			node = node->right;//new root becomes right child
			delete temp;
		}
		else if (node->right == NULL && node->left != NULL)
		{
			node = node->left;//new root becomes right child
			delete temp;
		}*/
		//if 2 children
		else //has 2 children
		{
			smallestRight = findSmallestPrivate(node->right);
			deleteCityPrivate(smallestRight->city.getName(), node);
			node->city = smallestRight->city;
		}
	
}

//-----------------------------DISPLAY---------------------------------------------------------
//public display
void BST::display()
{
	if (isEmpty()) {
		cout << "BTree is empty";
	}
	else {
		cout << root->city; //display root
		if (root->left != NULL) {
			cout << "Left" << endl;
			displayPrivate(root->left);
		}
		if (root->right != NULL) {
			cout << "right" << endl;
			displayPrivate(root->right);
		}
	}
}
//private display
void BST::displayPrivate(TreeNode * node)
{
	cout << node->city; //displays the node thats after the root
	if (node->left != NULL) {
		cout << "gone left //" << endl;
		displayPrivate(node->left);
	}
	if (node->right != NULL)
	{
		cout << "gone right \\" << endl;
		displayPrivate(node->right);
	}
}

//-------------------------MAIN----------------------------------------------------
int main() {

	BST tree;
	cout << "Enter city name\n";
	string name;
	cin >> name;

	cout << "coord 1";
	double lat;
	cin >> lat;

	cout << "coord 2";
	double lon;
	cin >> lon;
	cout << "----------------------" << endl;
	tree.insert(name, lon, lat);
	tree.insert("Arizona", 22.2, 14.1);
	tree.insert("London",23.2,34.1);
	tree.insert("Paris",89.3,64.2);
	tree.display();
	cout << "----------------------" << endl;
	tree.deleteCity("London");
	
	
	tree.display();
	
	system("pause");

};