// =====HEADER=====
// CS 170 Individual Project 1
// Name: Thien Chau
// SID: 861145164
// Discussion Section: 021
// =====HEADER=====
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <stdlib.h>

#include "UCS.h"
#include "aStarMisplacedTile.h"
#include "aStarManhattan.h"
#include "treeNode.h"
	
using namespace std;

int main(){
	
	//goal node
	node* goalNode;
	goalNode = new node;

	//initialize goal puzzle
	vector< vector<double> > goalPuzzle;
	goalPuzzle.resize(numCol, vector<double> (numRow, 0));
	goalPuzzle = setGoal(goalPuzzle);
	goalNode->puzzle = goalPuzzle;

	//root node
	node* n;
	n = new node;
	n->parent = NULL;

	//initialize default/user puzzle
	vector< vector<double> > eightPuzzle;
	eightPuzzle.resize(numCol, vector<double> (numRow, 0));

	int userChoice;
	while(true){
		//puzzle input
		cout << "Welcome to Thien Chau's 8-puzzle solver.\n";
		cout << "Type “1” to use a default puzzle, or “2” to enter your own puzzle.\n";
		cin >> userChoice;
	
		//user input
		if(userChoice == 2){
			string numAsString;
			int numAsInt;
			stringstream ss;
			cout << "Enter your puzzle, use a zero to represent the blank.\n";
			for(int i = 0; i < numRow; i++){
				cout << "Enter the elements for row " << i + 1 << ", use space between numbers: ";
				for(int j = 0; j < numCol; j++){
					if(j < numCol - 1){
						getline(cin, numAsString, ' ');
						ss<<numAsString;
						ss>>numAsInt;
						eightPuzzle.at(i).at(j) = numAsInt;
						ss.str("");
						ss.clear();		
					} else {
						getline(cin, numAsString);
						ss<<numAsString;
						ss>>numAsInt;
						eightPuzzle.at(i).at(j) = numAsInt;
						ss.str("");
						ss.clear();	
					}
				}
			}
			n->puzzle = eightPuzzle;
		}
		if(userChoice == 1){
			cout << "Enter the elements for row 1, use space between numbers: 4 2 8\n";
			cout << "Enter the elements for row 2, use space between numbers: 6 0 3\n";
			cout << "Enter the elements for row 3, use space between numbers: 7 5 1\n";
			eightPuzzle.at(0).at(0) = 4;
			eightPuzzle.at(0).at(1) = 2;
			eightPuzzle.at(0).at(2) = 8;
	
			eightPuzzle.at(1).at(0) = 6;
			eightPuzzle.at(1).at(1) = 0;
			eightPuzzle.at(1).at(2) = 3;
	
			eightPuzzle.at(2).at(0) = 7;
			eightPuzzle.at(2).at(1) = 5;
			eightPuzzle.at(2).at(2) = 1;
			n->puzzle = eightPuzzle;
	}
		
		if(solvable(n) == true){
			break;
		} else {
			cout << "Error: Puzzle entered is unsolvable. Program will restart." << endl << endl;
		}
	}	

	//algorithm selection
	userChoice = 0;
	cout << "Enter your choice of algorithm\n";
	cout << "\t1. Uniform Cost Search || 'f(n) = 0'\n";
	cout << "\t2. A* with the Misplaced Tile Heuristic || 'f(n) = g(n) + h(n)' where g(n) is the cost to get to the node and h(n) is the # of misplaced tiles\n";
	cout << "\t3. A* with the Manhattan distance heuristic || 'f(n) = g(n) + h(n)' where g(n) is the cost to get to the node and h(n) is the manhattan distance\n";
	cin >> userChoice;

	if(userChoice == 1) uniformCostSearch(n, goalNode); //perform Uniform Cost Search on root node n
	if(userChoice == 2) aStarMisplacedTile(n, goalNode); //perform A* with the Misplaced Tile Heuristic on root node n
	if(userChoice == 3) aStarManhattan(n, goalNode); //perform A* with the Manhattan distance heuristic on root node n

	//display solution
	displayPath(n);
	cout << endl << "Total nodes expanded(total nodes created): " << totalNodesExpanded + 1 /*+ 1 for parent node*/<< endl;
	cout << "Depth of solution: " << n->totalMoves << endl;
	cout << "Max number of nodes in queue:: " << maxNumOfNodesInQueue << endl;
	return 0;
}