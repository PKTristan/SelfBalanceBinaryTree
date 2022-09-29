#ifndef SBBTREE_H
#define SBBTREE_H
/*
Class Name: Self Balancing Binary Tree
Programmer Name: Tristan Calderon
Date: 11/29/2018

This class will be used to create a self balancing binary tree
which will read from a file, and display the tree in text based format.
This class will also allow a user to insert or delete nodes.
*/

//Include all necessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

//begin integer node class
class Node
{
public:
	int i;	//an integer i to hold the object in the node

	//node default constructor
	Node() :i(NULL)	//assigns null to i
	{
		left = nullptr;		//assigns the nullptr to left
		right = nullptr;		//assigns the nullptr to right
	}

	//consrtutor that takes in a value
	Node(int n) :i(n)	//assigns n to i
	{
		left = nullptr;		//assigns nullptr to left
		right = nullptr;		//assigns the nullptr to right
	}

	Node *left;		//creates a pointer to the lft node
	Node*right;		//creates a pointer to the right node
};

//begin balancing tree class
class SBBTree
{
private:
	Node* origin;		//a node pointer that will point to the origin node
	Node* curr;			//a node pointer that will point to the current node
	std::string file;		//a dtring to hold the file name
	int numOfNodes;		//track number of nodes

	//function to read from a file and create a tree
	void readFromFile()
	{
		std::ifstream myfile(file);		//open a file stream
		std::string line;		//create a string variable to hold each line in the file
		std::vector <int> num;		//create a vector of integers to store the integers from the file

		if (myfile.is_open())		//checks to see if file is open
		{
			while (getline(myfile, line))		//get the lines from the file in while loop 
			{
				num.push_back(stoi(line));		//put the integer into the vector
			}
		}
		else     //if the file did not open
		{
			system("cls");		//clear the screen
			std::cout << "FILE DID NOT OPEN";	//inform the user
		}

		if (num.size() != 0)		//if the vector isnt empty
		{
			int size = num.size();		//create an integer size tohold the size of the vector
			int x = size / 2;		//create an integer x that holds the value of half the vector size
			curr = origin = new Node(num[x]);		//make curr point to origin which points to a new node that holds the value of the number in vector at address x
			numOfNodes++;		//increment the num of nodes
			while (x != 0)		//while x does not equal 0
			{
				x = x / 2;		//make x = half of its value
				curr->left = new Node(num[x]);		//make the curr's left point to a new node with value of number in vector at adress x
				curr = curr->left;		//make curr point to the left node
				numOfNodes++;		//increment the num of nodes
			}
			curr = origin;		//make curr point to originagain
			x = size / 2;		//make x equal half the size of the vector again
			while (x != (size - 1))		//while x does not equla the size of the vector minus 1
			{
				x = x + (size - x) / 2 + (size - x) % 2;		//make x = size of the vector minus x dived my two plus size -x modulus 2
				curr->right = new Node(num[x]);		//make the curr's right point to a new node with ana ssignment
				curr = curr->right;		//make curr point to its right node
				numOfNodes++;		//increment the num of nodes
			}

			while (num.size() != 0)		//while the size of the vector does not equal 0
			{
				int n = num[num.size() - 1];		// n is equal to the size minus 1
				findNode(n, origin, nullptr);		// find the node that n has to be placed into and assign curr to point to it
				curr->i = n;		//make the node's i equal n
				num.pop_back();		//pop th elast value in the vector
			}
		}

	}

	//fucntion to find the node that needs to be inserted or deleted
	void findNode(int n, Node* t, Node* b)
	{
		curr = t;		//make curr equal the node befor

		if (curr == nullptr)		//if curr is the nullptr
		{
			if (b != nullptr)
			{
				if (b->i < n)
					curr = b->right = new Node();		//create a new node 
				else
					b->left = curr = new Node();
			}
			else
				curr = new Node();
			numOfNodes++;		//increment the number of nodes
		}
		else if (t->i < n)		// else if curr's i is less than n
			findNode(n, t->right, t);	//call to the cunction find node
		else if (t->i > n)		//else if curr's i is greater than n with curr's right
			findNode(n, t->left, t);		//call to function find node with curr's left
	}

	//private function to return the string of the LNR
	std::string getLNR(Node*t)
	{
		std::string lnr;		//create a string to hold the values

		if (t->left != nullptr)		//if t's left is not the nullptr
			lnr = getLNR(t->left);		// call to the get order function that assigns its return to lnr

		lnr = lnr + std::to_string(t->i) + " ";		//adds the value of this t's i to the lnr string

		if (t->right != nullptr)		//if the t's right is not the nullptr
			lnr = lnr + getLNR(t->right);		// assign the return of the call to this function 

		return lnr;		//return string
	}

	//private function to return the string of the LNR
	void vectLNR(Node*t, std::vector <std::string> &vect, int level)
	{
		int maxH = log2(numOfNodes);
		if (t->left != nullptr)		//if t's left is not the nullptr
			vectLNR(t->left, vect,level + 1);	// call to the get order function that assigns its return to lnr
		else if (level != maxH)
			vect.push_back("   ");

		vect.push_back(std::to_string(t->i));		//adds the value of this t's i to the lnr string

		if (t->right != nullptr)		//if the t's right is not the nullptr
			vectLNR(t->right, vect,level + 1);		// assign the return of the call to this function 
		else if (level != maxH)
			vect.push_back("   ");
	}

	//private function to return the string of NLR
	std::string getNLR(Node*t)
	{
		std::string lnr;		//create a string to hold the values of the nodes in pre order

		lnr = std::to_string(t->i) + " ";		//assign lnr to the value of i in t

		if (t->left != nullptr)		// if t's lef tis not the nulllptr
			lnr = lnr + getNLR(t->left);		//add the retutrn of the call to this function with the left of this t

		if (t->right != nullptr)		//if the t's right is not the nullptr
			lnr = lnr + getNLR(t->right);		// add the return of the call to this function with the t's right

		return lnr;		// return the string
	}

	//private function to return the string of the LRN
	std::string getLRN(Node*t)
	{
		std::string lnr;		//create a string to hold the values

		if (t->left != nullptr)		//if t's left isnt the nullptr
			lnr = getLRN(t->left);		// assign the value of the lnr to return of the call to this function

		if (t->right != nullptr)		//if t's right isnt the nullptr
			lnr = lnr + getLRN(t->right);		//call to this function with t's right

		lnr = lnr + std::to_string(t->i) + " ";		//add this t's value to the string

		return lnr;			//return the string
	}

	//private function to rotate a node to the right
	void rightRotate(Node* t, Node* o)
	{
		curr = o;		//curr points to o which is origin of subtree/tree

		while (curr->left != t)		//while the left of curr isnt t
		{
			if (curr->i > t->i)		//iff the value of curr is greater than the value of t
				curr = curr->left;		//curr points to the left node
			else if (curr->i < t->i)		//els eif val of curr is less than t
				curr = curr->right;		//curr points to the right
		}

		if (t->right != nullptr)		//if t's right isnt the nullptr
			curr->left = t->right;		//curr's left now points to t's riht
		else
			curr->left = nullptr;		//if t 's right does not have a node, make curr's left null

		t->right = curr;		//t's right now points to curr

		if (curr != origin)		//if curr isnt the origin
		{
			curr = origin;		//curr now equals the origin

			while (curr->right != t->right && curr->left != t->right)		//while curr's right and left don't equal t's right
			{
				if (curr->i > t->i)		//if curr's val is greater than i's value
					curr = curr->left;		//traverse left
				else if (curr->i < t->i)		//else if curr's value is less than t's
					curr = curr->right;		//traverse right
			}

			if (curr->right == t->right)		//if curr's right is equal to t's right
				curr->right = t;		//make curr's right point to t
			else if (curr->left == t->right)		//els if curr's left is equal to t's right
				curr->left = t;		//make curr's left point to t
		}
		else     //else if curr is th origin
		{
			origin = t;			//t is the new origin
		}
	}

	//private function to rotate a node left
	void leftRotate(Node *t, Node* o)
	{
		curr = o;		//make curr equal to the origin of tree/subtree

		while (curr->right != t)		//while curr's right is not t
		{
			if (curr->i > t->i)		//if curr's value is greater than t's
				curr = curr->left;		//traverse left
			else if (curr->i < t->i)		//else if curr's value is less than t's
				curr = curr->right;		//travers right
		}

		if (t->left != nullptr)		////if t's left is not the nullptr
			curr->right = t->left;		//make curr's right point to t's left
		else
			curr->right = nullptr;		//make curr's right null

		t->left = curr;		//make t's left point to curr

		if (curr != origin)		//if curr is not the origin	
		{
			curr = origin;		//make curr point to the origin	

			while (curr->left != t->left && curr->right != t->left)		//while curr's left and right arent t's left
			{
				if (curr->i > t->i)		//if curr's value is greater than t
					curr = curr->left;		//traverse left
				else if (curr->i < t->i)		//else if curr's value is less than t's
					curr = curr->right;		//traverse right
			}

			if (curr->left == t->left)		//if curr's left is equal to t's left
				curr->left = t;		//curr's left is equal to t
			else if (curr->right == t->left)		//else if curr's right is equal to t's left
				curr->right = t;		//curr's right is equal to t
		}
		else     //if curr is equal to the origin
		{
			origin = t;		//t is the new origin
		}
	}

	//function that shifts the median number to the origin of the tree/subtree
	Node * shiftMiddle(Node *t, int non)
	{
		Node * tempCurr = t;		//create a temporary curr that points to the t
		std::vector <char> path;		//create a vector named path that keeps track of where the median number is from t
		int val;		//an int that holds the value of the median number
		int posOfVal = -1;		//an integer that holds the position of the value in context to string vals
		std::string vals = getLNR(t);		//string vals that will hold the string given by getLNR

		for (int m = 0; m < ((non / 2) + (non % 2) - 1); m++)		//a for loop to find the position of the value we need
		{
			posOfVal = vals.find(" ", posOfVal + 1)+1;		//make the position of thevalue equal the posOfVal integer
		}

		vals = vals.substr(posOfVal, std::string::npos);		//make a substring from the begining of that value to the end of the string
		posOfVal = vals.find(" ", 0);		//find the end of the value in the string
		vals = vals.substr(0, posOfVal);		//make a subsring that cuts off the end so we only have a string containing the value

		val = stoi(vals);		//make val equal the value from the string

		while (tempCurr->i != val)		//while the value in the current node isnt the value we seek
		{
			if (tempCurr->i > val)		//if the value n the current node is greter than val
			{
				tempCurr = tempCurr->left;		//we travers left
				path.push_back('l');		//then we psuh l into the path to represent a traversal to the left
			}
			else if (tempCurr->i < val)		//else if the vslue is less
			{
				tempCurr = tempCurr->right;		//we traverse right
				path.push_back('r');		//we push rinto the vetor to represnt a traversal right
			}
		}

		while (path.size() != 0)		//while the size of the vector is not zero
		{
			if (path[path.size() - 1] == 'l')		//if the character in the last entry of the vector is l
				rightRotate(tempCurr, t);		//we first right rotate the current node
			else if (path[path.size() - 1] == 'r')		//else if the charater is an r
				leftRotate(tempCurr, t);		//we first left rotate

			path.pop_back();		//we get rid o the last entry in the vector
		}

		return tempCurr;
	}

	//function to check if the tree is balanced
	void checkBalance(Node * t, int non)
	{
		if (t != nullptr)
		{
			int heightMax = log2(non);		//gets the maximum height the tree/subtree should be based on the number of nodes
			int rHeight = getHeight(t->right, 0);		//gets the height of the right side of the tree/subtree
			int lHeight = getHeight(t->left, 0);		//gets the height of the left sid eof the tree/subtree

			if (heightMax < rHeight || heightMax < lHeight)		//if the maximum height it should be is less than either the left or right
			{
				t = shiftMiddle(t, non);		//we find the median number, and we make it the origin of the tree/subtree
				checkBalance(t->left, ((non / 2) + (non % 2) - 1));		//we recheck to see if the tree is balanced or not on the left
				checkBalance(t->right, non / 2);		//or the right
			}
		}
	}


	//private function to get the height of the subtree
	int getHeight(Node*t, int h)
	{
		if (t != nullptr)		//if t is not the nullptr
		{
			h++;		//h which is initial height is incrementes
			if (t->left != nullptr || t->right != nullptr)		//if t's left or right isnt the nullptr
			{			
				int r = getHeight(t->right, h);		//integer r is equal to the return of the call fo this function 
				int l = getHeight(t->left, h);		//integer l is equal to the return of the call of this function
				if (h < l)		//if h is less than l
					h = l;		//h is equal to l

				if (h < r)		//if h i less than r
					h = r;		//h is equal to r
			}
		}

		return h;		//return h
	}

public:
	//default constructor
	SBBTree() :numOfNodes(0)	//assign null to file
	{
		curr = origin = nullptr;		//assigns nullptr to origin and curr
	}

	//constructor that takes first node value
	SBBTree(int n) :numOfNodes(0)		//assign null to file
	{
		curr = origin = new Node(n);	//assigns both curr and origin to a new node with value n
	}

	//constructor that takes the name of a file and creates a tree from that info
	SBBTree(std::string filename) :file(filename), numOfNodes(0)		//assign filename to file
	{
		curr = origin = nullptr; //assigns nulltpr to curr and origin
		readFromFile();		//calls function that creates tree from a file
	}

	//fucntiont that returns a string for printing with the noddes in order
	std::string getInOrder()
	{
		return getLNR(origin);		//return the result of the call to the getLNR function
	}

	//function that returns a string with the values of the nodes in preorder
	std::string getPreOrder()
	{
		return getNLR(origin);		//return the call to the getNLR function
	}

	//function that returns a string for printing with the nodes in post order
	std::string getPostOrder()
	{
		return getLRN(origin);		//return the call to the getLRN ucntioon
	}

	//function to insert a node
	void insertNode(int val)
	{
		findNode(val, origin, nullptr);		//call to function find node fo know where to insert the node
		curr->i = val;		//assign the new node's i to the val
		if (origin == nullptr)
			origin = curr;
		checkBalance(origin, numOfNodes);		//call to the checkBalance function to rebalance the tree

	}

	//function to get the heigt of the tree
	int getTreeHeight()
	{
		return getHeight(origin, -1);		//returns call to the getHeight function with origin and -1 as parameters
	}

	//function to delete a node
	void deleteNode(int val)
	{
		findNode(val, origin, nullptr);		//call to function to find node to delete
		if (curr == origin)		//if deleting the origin
		{
			if (curr->right == nullptr && curr->left == nullptr)		//if the origin is the only node
			{
				delete(curr);		//delete the origin
				curr = origin = nullptr;		//make curr and origin equal the nullptr
			}
			else if (curr->right == nullptr)		//else if the right of the origin is nulllptr
			{
				origin = curr->left;		//left become the new origin
				delete(curr);		//delete the old origin
				curr = nullptr;		//curr is nullptr
			}
			else if (curr->left == nullptr)		//else if the left has no node
			{
				origin = curr->right;		//right becomes the new origin
				delete(curr);		//delete old origin
				curr = nullptr;		//curr is nullptr
			}
			else     //else if there are more than 3 nodes
			{
				if (curr->right->left == nullptr)		//if the left of the right to the origin is null
					curr->right->left = curr->left;		//the right becomes the new origin
				else    //else 
				{
					Node* t = curr->left;		//temporarynode t points to the left of the origin
					while (t->right != nullptr)		// while the right of t is not nullptr
					{
						t = t->right;		//traverse right
					}
					t->right = curr->right->left;		//when at the end, make t's right point to the origin's right's left
					curr->right->left = curr->left;		//make the origin's right the new origin
				}

				origin = curr->right;		////the right is the new origin
				delete(curr);		//delete the old origin
				curr = nullptr;		//curr is nullptr
			}
		}
		else if (curr->right != nullptr || curr->left != nullptr)		//else if at least the right or left of the node is not empty
		{
			if (curr->right->left == nullptr)		//if the right's left is the nullptr
				curr->right->left = curr->left;		//the right of this node's left points to the left of this node
			else    //else
			{
				Node* t = curr->left;		//make temporary node t point to the curr's left
				while (t->right != nullptr)		//while t's right is not empty
				{
					t = t->right;		//traverse right
				}
				t->right = curr->right->left;		//make the left of the right node to curr be pointed to by the t's right
				curr->right->left = curr->left;		//make the left of curr's right point to curr's left
			}

			Node*prev = origin;		//create a new ndoe prev that points to origin
			while (prev->right != curr && prev->left != curr)		//while prev doesnt point to curr
			{
				if (prev->i > curr->i)		//if prev's val is greater than curr's value
					prev = prev->left;		//traverse left
				else if (prev->i < curr->i)		//else if prev's value is less than curr's
					prev = prev->right;		//traverse right
			}

			if (prev->right == curr)		//if prev's right points to curr
				prev->right = curr->right;		//prev's right now points to curr's right
			else if (prev->left == curr)		//if prev's left points to curr
				prev->left = curr->right;		//prev's left now points to curr's right

			delete(curr);		//delete curr
			curr = nullptr;		//curr is nullptr
		}
		else     //else if curr is a leaf only
		{
			Node *t = origin;		//create a temp node	
			while (t->right != curr && t->left != curr)		//if t's node doesnt point to curr
			{
				if (t->i > curr->i)		//if cur is smaller than t
					t = t->left;		//traverse left
				else if (t->i < curr->i)		//if curr is bigger thn t
					t = t->right;		//traverse right
			}

			if (t->right == curr)
				t->right = nullptr;
			else if (t->left == curr)
				t->left = nullptr;

			delete(curr);		//delete curr
			curr = nullptr;		//curr is nullptr
		}

		numOfNodes--;		//decrement the numOfNodes 

		checkBalance(origin, numOfNodes);		//checkBalance to rebalance
	}

	//function to save the Tree to the file that is open
	void writeToFile()
	{
		if (file.empty())		//if the string with the file name is empty
		{
			std::cout << "Please enter name of file: ";		//tell the user to enter the name of the file
			getline(std::cin, file);		//get the name of the file
		}

		std::ofstream myFile(file);		//open an output file stream
		std::string line;		//create a string line
		std::string val;		//create a string val
		int pos = -1;		//a string to keep track of the positions of spaces
		int opos;		//a string to keep track of old positions of spaces
		int value;		//integer to hold the string value

		if (myFile.is_open())		//if the file is open
		{
			line = getInOrder();		//get the inorder string

			for (int i = 0; i < numOfNodes; i++)		//loop for the number of nodes in the tree
			{
				opos = pos + 1;		//save the old position +1

				pos = line.find(' ', opos);		//find the position of the new space character

				val = line.substr(opos, pos);		//val is equal to the substring containing the value of the integer

				value = stoi(val);		//value is equal to the integer

				myFile << value << std::endl;		//save to the file
			}
		}
		else
			std::cout << "Error openning file.";		//if the file is not open tell the user

		myFile.close();		//close file
	}

	//function to display the tree
	void displayTree()
	{
		std::vector <std::string> vect;		//vector to hold string 
		vectLNR(origin, vect, 0);		//add to vector the nodes
		int stop = log2(numOfNodes);		//make a stopper
		int beg = vect.size() / 2;		//make a begginning of the line
		int spaces = (pow(2, stop) * 5) / 2;	//add spaces between each nodde value
		int prevSpaces = 0;		//keep track of previous spaces


		for (int i = 0; i <= stop; i++)		//for loop to display the tree
		{
			int addSpaces = 0;
			for (int j = beg; j < vect.size();)
			{
				for (int m = 0; m < (spaces + addSpaces); m++)		//for loop to add spaces
					std::cout << " ";
					
				addSpaces = (prevSpaces - spaces - (prevSpaces % 2)) * 2 - spaces;
				std::cout << vect[j];		//display value of nodes

				j = j + (2 * (beg + 1));
			}
			prevSpaces = spaces;
			spaces = spaces / 2;
			beg = beg / 2;
			std::cout << std::endl;		//when the end of a line is reached go to next line
		}

	}

};



#endif
