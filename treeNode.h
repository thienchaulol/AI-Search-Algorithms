#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <vector>
#include <stdlib.h>


//puzzle specifications
int numRow = 3;
int numCol = 3;

using namespace std;

//nodes of puzzle states
struct node{
	vector< vector<double> > puzzle;
	//node pointers used to create new nodes
	node* swapLeft = 0;
	node* swapRight = 0;
	node* swapTop = 0;
	node* swapBot = 0;
	//node pointer to point back to parent
	node* parent = NULL;
};

#endif

