#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <vector>
#include <stdlib.h>
#include <iostream>

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
	
	//bool values to check which route parent took
	//used for heuristics that get stuck
	bool tookLeft = false;
	bool tookRight = false;
	bool tookTop = false;
	bool tookBot = false;
	
	//node pointer to point back to parent
	node* parent = NULL;
	//string to know what move parent made
	//when creating child's children, do not create a child
	//that would be the opposite of the parent's parent's move.
	//when you swap left, set swapMove = left
	//in the next iteration, when creating children, if swapMove == "left", do not create a swapRight child node
	string swapMove = "";
	//int to check for diameter of 8 puzzle
	int totalMoves = 0;
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
	//displayPuzzle(x);
	displayVector.push_back(x);
	while(true){
		if(x->parent != NULL){
		//	cout << "Storing node puzzle in vector" << endl;
			displayVector.push_back(x->parent);	//x->parent is NULL
			x = x->parent;
		} else {
			cout << "Finished storing path into display vector" << endl;
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
	cout << "Finished displaying path to solution" << endl;
}

//check if puzzle is solvable
bool solvable(node* x){
	vector<double> testMatrix;
	
	for(int i = 0; i < numRow; i++){
		for(int j = 0; j < numCol; j++){
			if(x->puzzle.at(i).at(j) != 0){
				testMatrix.push_back(x->puzzle.at(i).at(j));
			}
		}
	}
	
	int inversions = 0;
	for(int i = 0; i < testMatrix.size(); i++){
		for(int j = i + 1; j < testMatrix.size(); j++){
			if(testMatrix.at(j) > testMatrix.at(i)){
				inversions++;
			}
		}
	}
	
	if(inversions % 2 == 1){
		return false; //unsolvable
	} else if(inversions % 2 == 0) {
		return true; //solvable
	}
}

//record parent direction incase heuristic fails(if, at any state, all heuristics are equal)
void recordParentDirection(node* x, string y){
	if(x->parent == NULL){
		if(y == "swapRight"){
			x->parent->tookRight = true;
		}
		if(y == "swapLeft"){
			x->parent->tookLeft = true;
		}
		if(y == "swapTop"){
			x->parent->tookTop = true;
		}
		if(y == "swapBot"){
			x->parent->tookBot = true;
		}
	}
	return;
}

//choose different root direction when heuristic fails
node* chooseDifferentDirection(node* x){
	cout << "Choosing different direction" << endl;
	while(x->parent != NULL){
		x = x->parent;
	}
	return x;
}

#endif

