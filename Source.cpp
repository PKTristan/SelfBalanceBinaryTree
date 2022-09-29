#include "SBBTree.h"
#include<iostream>

using namespace std;

void main()
{
	bool exit = false;		//value to keep track of when user wants to exit program
	string str;		//string to hold all string values needed
	//ask the user for input
	cout << "Please enter the name of the file you wish to open (ExampleTree.txt): ";
	getline(cin, str);		//get file name
	SBBTree tree(str);		//create tree with filename

	cout << "Press enter to continue...";		//prompt them to press enter when ready to continue
	cin.ignore();

	while (!exit)		//while they didnt choose exit
	{
		system("cls");		//cclear screen

		tree.displayTree();		//display tree

		//display the menu which tells user how to use program
		cout << endl << "Insert Node: type I or i followed by number (I34)" << endl;
		cout << "Delete Node: type D or d followed by number (D22)" << endl;
		cout << "Pre Order: type P1 or p1" << endl;
		cout << "In Order: type P2 or p2" << endl;
		cout << "Post Order: type P3 or p3" << endl;
		cout << "Write to file and Exit:  type E or e" << endl;

		getline(cin, str);		//get the user input

		//start deciding what to do
		if (str.at(0) == 'I' || str.at(0) == 'i')		//insert
		{
			int val = stoi(str.substr(1, str.npos));	//parse string

			tree.insertNode(val);		//inster value
		}
		else if (str.at(0) == 'D' || str.at(0) == 'd')		//delete
		{
			int val = stoi(str.substr(1, str.npos));		//parse string

			tree.deleteNode(val);		//delete val
		}
		else if (str.at(0) == 'P' ||str.at(0) == 'p')		//get values
		{
			if (str.at(1) == '1')		//preorder
				str = tree.getPreOrder();//assign the pre order to str
			else if (str.at(1) == '2')		//in order
				str = tree.getInOrder();	//assign in order to str
			else if (str.at(1) == '3')		//post order
				str = tree.getPostOrder();		//assign post order to str

			system("cls");		//clear screen

			cout << str;	//prin tthe string

			cout << endl << "Press enter to continue...";

			cin.ignore();		//press enter to continue
		}
		else if (str.at(0) == 'E' || str.at(0) == 'e')		//exit
		{
			tree.writeToFile();		//save the nodes to the file
			exit = true;		//make exit true
		}
	}


	cin.ignore();
}
