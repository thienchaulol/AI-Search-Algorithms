// =====HEADER=====
// CS 170 Individual Project 1
// Name: Thien Chau
// SID: 861145164
// Discussion Section: 021
// =====HEADER=====
#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <vector>
#include <stdlib.h>
#include <iostream>

//puzzle specifications
int numRow = 3;
int numCol = 3;

//total number of nodes expanded by algorithm
int totalNodesExpanded = 0;	//everytime you create children, do "totalNodesExpanded++;"

//maximum number of nodes in queue during algorithm
int maxNumOfNodesInQueue = 0;

//depth of goal node
//int depthOfGoalNode = 0;	//depth of solution is totalMoves, lucky you

//CHANGING GOAL STATE: HARDCODE setGoal() to new goal state. OR make function to input new goal state

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
	//int to check for diameter of 8 puzzle. can be used to find solution node depth
	int totalMoves = 0;
};


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

//set goal puzzle
vector< vector<double> > setGoal(vector< vector<double> > x){
	//default solution puzzle...1 2 3
	//							4 5 6
	//							7 8 0
	int k = 0;
	for(int i = 0; i < numRow; i++){
		for(int j = 0; j < numCol; j++){
			k++;
			if(k < 9) x.at(i).at(j) = k;
		}
	}
	
	//custom solution puzzle... ? ? ?
	//							? ? ?
	//							? ? ?
	// x.at(0).at(0) = ;
	// x.at(0).at(1) = ;
	// x.at(0).at(2) = ;
	
	// x.at(1).at(0) = ;
	// x.at(1).at(1) = ;
	// x.at(1).at(2) = ;
	
	// x.at(2).at(0) = ;
	// x.at(2).at(1) = ;
	// x.at(2).at(2) = ;

	
	node* temp = new node;
	temp->puzzle = x;
	if(solvable(temp) == true){
		return temp->puzzle;
	} else {
		cout << "Error: Goal state not solvable. Exit(0)." << endl;
		exit(0);
	}
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
		//	cout << "Finished storing path into display vector" << endl;
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

