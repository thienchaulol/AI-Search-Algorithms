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


//set goal puzzle
vector< vector<double> > setGoal(vector< vector<double> > x){
	int k = 0;
	for(int i = 0; i < numRow; i++){
		for(int j = 0; j < numCol; j++){
			k++;
			if(k < 9) x.at(i).at(j) = k;
		}
	}
	return x;
}

//display puzzle node
void displayPuzzle(node* x){
	for(int i = 0; i < numRow; i++){
		for(int j = 0; j < numCol; j++){
			cout << x->puzzle.at(i).at(j) << " ";
		}
		cout << endl;
	}
}

//display moves to get to puzzle goal
void displayPath(node* x){
	vector< node* > displayVector;
	displayVector.push_back(x);
	while(true){
		if(x->parent != NULL){
			displayVector.push_back(x->parent);	//x->parent is NULL
			x = x->parent;
		} else {
			cout << "finish while loop " << endl;
			break;
		}
		
	}
	int j = 0;
	for(int i = displayVector.size() - 1; i > 0; i--){	//decrement size() twice because parent of root node is NULL
		cout << "Move: " << j << endl;
		displayPuzzle(displayVector.at(i - 1));
		cout << endl;
		j++;
	}
}

#endif

