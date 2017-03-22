#include <iostream>
#include <map>
#include <string>
#include "City.h"
#include "TreeNode.h"
#include "timer.h"
using namespace std;
//MAIN AT BOTTOM OF THIS FILE

class BST {
	//friend class TreeNode;

public:
	BST();
	~BST();
	void insert(string name, double lon, double lat);//insert by name, create new obj of city
	void deleteCity(string name);//delete by name
	void display();
	bool isEmpty();
	int height();
	void Inorder( string n);
	void Postorder( string n);
	void Preorder(string n);
	bool searchName(string name);
	bool searchCoord(double lon,double lat);
private:
	TreeNode * root;
	void insertPrivate(TreeNode *newNode, TreeNode *curr);//private insert method to allow for recursion
	void displayPrivate(TreeNode *newNode);
	int getHeight(TreeNode* node);
	TreeNode* findSmallestPrivate(TreeNode *newNode);
	void deleteCityPrivate(string name, TreeNode *&node);//delete city method allowing access to root
	void Remove(TreeNode *&nodeToDel);
	bool searchNamePrivate(TreeNode *root, string name);
	bool searchCoordPrivate(TreeNode *node, double lon, double lat);
	void printkdistanceNodeDown(TreeNode *root, int k);
	int printkdistanceNode(TreeNode* root, TreeNode* target, int k);
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
			return findSmallestPrivate(node->left);
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
void BST::deleteCityPrivate(string n, TreeNode *&parent)
{
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

void BST::Remove(TreeNode *&node)//prepares the node for deletion 
{
	TreeNode *temp = new TreeNode();
	if (node->right != NULL && node->left != NULL) //
	{
		TreeNode* smallest = new TreeNode();
		smallest = findSmallestPrivate(node->left);
		string smallestName;
		smallestName = smallest->city.getName();
		node->city = smallest->city;
		deleteCityPrivate(smallestName, node->left);

	}
	else
	{
		//if only left children
		if (node->right == NULL && node->left != NULL)//go left
		{
			temp = node;//once found node set to temp 
			node = node->left;
			delete temp; 
		}
		//else if only right children
		else
		{
			temp = node;
			node = node->right;
			delete temp;
		}
	}
}
//----------------------------TRAVERSALS-------------------------------------------------------

void BST::Preorder(string n)
{
	TreeNode *node = root;
	if (node->city.getName() == n)
	{
		cout << node->city.getName() << " ";
		Preorder(node->left->city.getName());
		Preorder(node->right->city.getName());
	}
}

void BST::Inorder(string n)
{
	if (root != NULL)
	{
		Inorder(root->left->city.getName());
		cout << root->city.getName() << endl;
		Inorder(root->right->city.getName());

	}
}

void BST::Postorder( string n)
{
	if (root != NULL)
	{

		Postorder(root->left->city.getName());
		Postorder(root->right->city.getName());
		cout << root->city.getName() << endl;

	}
}

//-----------------------------Search---------------------------------------------------------
/*
*usage : used/modified
*author: Newbie25
*title: Binary search tree search function
*date: 19/03/17
*url: http://www.dreamincode.net/forums/topic/173416-binary-search-tree-search-function/
*/
bool BST::searchNamePrivate(TreeNode *root,string name)  {
	if (root != NULL) {

		// check if current node has the element we are looking for
		if (root->city.getName() == name) {
			return true;
			cout << "Found City: " << name << endl;
		}
		else {
			// check if the sub trees
			return searchNamePrivate(root->left, name) || searchNamePrivate(root->right, name);
			cout << "Found City: " << name << endl;
		}
	}
	return false;
	cout << "City: " << name << " not found"<< endl;
}
bool BST::searchName(string name)
{
	return searchNamePrivate(root, name);
}
/*
bool BST::searchCoordPrivate(TreeNode *node, double lat, double lon)
{
	if (root != NULL)
	{
		if (node->city.getLong() == lon && node->city.getLat() == lat)
		{
			return node;
		}
		else
		{
			return searchCoordPrivate(node->left, lat, lon) || searchCoordPrivate(root->right, lat, lon);
			cout << "Found City: " << node->city.getName() << endl;
		}
	}
	return false;
	cout << "Co-ordinates not found" << endl;

	
}
bool BST::searchCoord(double lon, double lat)
{
	return searchCoordPrivate(root, lon, lat);
}
*/
//-----------------------------HEIGHT---------------------------------------------------------

int BST::height()
{
	if(isEmpty())
	{
		return -1;
	}
	else 
	{
		return getHeight(root);
	}
	
}
int BST::getHeight(TreeNode* node)
{
	if (node == NULL)
	{
		return -1;
	}
	int left = getHeight(node->left);
	int right = getHeight(node->right);

	if (left > right)
	{
		return 1 + left;
		cout << " left is deeper" << endl;
	}
	else
	{
		return 1 + right;
		cout << " right is deeper" << endl;
	}
}
//-----------------------------DISTANCE CALC---------------------------------------------------

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
		cout << "gone left /// " << endl;
		displayPrivate(node->left);
	}
	if (node->right != NULL)
	{
		cout << "gone right \\\ " << endl;
		displayPrivate(node->right);
	}
}

//-------------------------MAIN----------------------------------------------------
int main() {

	BST tree;

	tree.insert("Dublin", 53.3498, -6.2603);
	tree.insert("Manchester", 53.4808, 2.2426);
	tree.insert("London", 23.2, 34.1);
	tree.insert("Arizona", 22.2, 14.1);
	tree.insert("Edinburgh", 55.9533, -3.1883);
	tree.insert("Paris", 48.8566, 2.3522);
	tree.insert("New York", 40.7128, -74.0059);
	tree.insert("Krakow", 50.0647, 19.9450);
	tree.insert("Sicily", 37.3979, 14.6588);

	
	tree.display();
	cout << "-----------------------------" << endl;
	cout << tree.height() << endl;
	cout << "-----------------------------" << endl;
	tree.deleteCity("London");
	tree.display();
	cout << "-----------------------------" << endl;
	cout << tree.searchName("Paris") << endl;
	//cout << tree.searchCoord(37.3979, 14.6588) << endl;
	cout << "-----------------------------" << endl;
	// tree.Inorder("Dublin");
	 cout << "-----------------------------" << endl;
	 cout << "////STARTING ANALYSIS OF ALGORITHMS" << endl;
	
	 /*
	 double wall0 = get_wall_time();
	 double cpu0 = get_cpu_time();
	 tree.searchName("London");
	 double wall1 = get_wall_time();
	 double cpu1 = get_cpu_time();
	 cout << "Wall Time = " << wall1 - wall0 << endl;
	 cout << "CPU Time  = " << cpu1 - cpu0 << endl;
	
	*/
	 system("pause");

};