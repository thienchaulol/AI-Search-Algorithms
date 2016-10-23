#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <vector>

//puzzle specifications
int numRow = 3;
int numCol = 3;

using namespace std;

//nodes of puzzle states
struct node{
	vector< vector<double> > puzzle;
	//node pointers used to create new nodes
	node* swapLeft;
	node* swapRight;
	node* swapTop;
	node* swapBot;
	//node pointer to point back to parent
	node* parent;
};

#endif