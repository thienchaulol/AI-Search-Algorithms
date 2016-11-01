#ifndef ASTARMISPLACEDTILE_H_INCLUDED
#define ASTARMISPLACEDTILE_H_INCLUDED

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include "treeNode.h"

using namespace std;

//aStarMisplacedTile is same as UCS except it continues on the node with less steps to the goal
//  so, have a counter: "int totalMisplacedTiles" and instead of searching Q.front() every the time before moving on,
//  iterate through the data structure(most likely list or vector) and pick the element that has the least amount
//  of totalMisplacedTiles

int findMisplacedTiles(node* x, node* goal){
    int totalMisplacedTiles = 0;
    for(int i = 0; i < numRow; i++){
        for(int j = 0; j < numCol; j++){
            if(x->puzzle.at(i).at(j) != goal->puzzle.at(i).at(j) && x->puzzle.at(i).at(j) != 0){
                totalMisplacedTiles++;
            }
        }
    }
    return totalMisplacedTiles;
}

int findMin(int w, int x, int y, int z){
	vector<int> temp;
	if(w != 2480){
		temp.push_back(w);
	}
	if(x != 2480){
		temp.push_back(x);
	}
	if(y != 2480){
		temp.push_back(y);
	}
	if(z != 2480){
		temp.push_back(z);
	}
	int lowest = temp.front();
	for(int i = 0; i < temp.size(); i++){
		if(temp.at(i) < lowest){
			lowest = temp.at(i);
		}
	}
//	cout << "Lowest: " << lowest << endl;
	return lowest;
}

//can't solve complex 8 puzzles
void aStarMisplacedTile(node* &x, node* goal){
	vector< vector<double> > solvableCase;
	solvableCase.resize(numCol, vector<double> (numRow, 0));
	
	solvableCase.at(0).at(0) = 1;
	solvableCase.at(0).at(1) = 2;
	solvableCase.at(0).at(2) = 3;

	solvableCase.at(1).at(0) = 4;
	solvableCase.at(1).at(1) = 5;
	solvableCase.at(1).at(2) = 6;

	solvableCase.at(2).at(0) = 7;
	solvableCase.at(2).at(1) = 0;
	solvableCase.at(2).at(2) = 8;
	//check if user puzzle is equal to goal puzzle
	if(x->puzzle == goal->puzzle){
		cout << "Puzzles are equal; return\n";
		return;
	} else {
		cout << "Puzzles are not equal; search \n";
	}
	
	node* currentNode;
	node* temp;
	
	//TODO: add fix when puzzle gets stuck

	int emptyTileRow = 0;
	int emptyTileCol = 0;
	bool popLater; //bool to pop node after creating it's children
	bool checkpoint = false;    //checkpoints to prevent duplicate puzzles
	bool checkpoint2 = false;
	bool checkpoint3 = false;
	bool isRoot = false;
	
	queue< node* > Q;
	Q.push(x);
	x->totalMisplacedTiles = findMisplacedTiles(x, goal);
	
	while(!Q.empty()){
		//10.29.16 6:01 PM
		//	have a queue. push the child with the lowest misplaced tiles onto queue, pop parent
		//	loop until find solution
		//	if, at any state, all the LOWEST MPT are the same value, iterate back up to parent (while (Q.front()->parent != NULL)) Q.front() = Q.front()->parent;
		//		then choose a path you haven't taken
		//	if you get stuck, get it to function first before perfecting it(professor's words)
		//
		//	at the end of every if statement, only push the node that has more misplaced tiles
		//		compare the totalMisplacedTiles of all children
		//10.31.16
		// the problem with this implementation of the algorithm is: how you calculate the heuristic, and
		// how you use it to choose the next node to push onto the queue!

		if(Q.front()->parent == NULL){
			isRoot = true;
		} else {
			isRoot = false;
		}

		displayPuzzle(Q.front());
		cout << endl;
	//	cout << "Q.front()->totalMisplacedTiles: " << Q.front()->totalMisplacedTiles << endl;

		//check if puzzle is solvable
		if(solvable(Q.front()) == false){
			cout << "Error: Puzzle is not solvable" << endl;
			return;
		} //segfault

		//find front node's empty tile, store row/column value
		//create nodes of swappable states. use swap()
		for(int i = 0; i < numRow; i++){
			for(int j = 0; j < numCol; j++){
				if(Q.front()->puzzle.at(i).at(j) == 0){
					emptyTileRow = i;
					emptyTileCol = j;
				}
			}
		}

		//if top row is 1 2 3, do not switch puzzle.at(0).at(0), puzzle.at(0).at(1), and puzzle.at(0).at(2)
		if(Q.front()->puzzle.at(0).at(0) == 1 && Q.front()->puzzle.at(0).at(1) == 2 && Q.front()->puzzle.at(0).at(2) == 3 && checkpoint2 == false){
			checkpoint = true;
		}
		if(Q.front()->puzzle.at(0).at(0) == 1 && Q.front()->puzzle.at(0).at(1) == 2 && Q.front()->puzzle.at(0).at(2) == 3 && Q.front()->puzzle.at(1).at(0) == 4 && checkpoint3 == false){
			checkpoint2 = true;
		}
		if(Q.front()->puzzle.at(0).at(0) == 1 && Q.front()->puzzle.at(0).at(1) == 2 && Q.front()->puzzle.at(0).at(2) == 3 && Q.front()->puzzle.at(1).at(0) == 4 && Q.front()->puzzle.at(2).at(0) == 7){
			checkpoint3 = true;
		}

		popLater = false;
		if(Q.front()->puzzle == goal->puzzle){
			cout << "PUZZLE FOUND; exit" << endl;
			x = Q.front();	//set original node to solution node
			return;
		} else if(Q.front()->puzzle == solvableCase){
			cout << "Puzzle FOUND; exit2" << endl;
			if(Q.front()->swapMove != "swapLeft"){
				node* temp21 = new node;
				temp21->puzzle = Q.front()->puzzle;
				swap(temp21->puzzle.at(emptyTileRow).at(emptyTileCol), temp21->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp21;
				temp21->parent = Q.front();
				temp21->swapMove = "swapRight";
				Q.push(temp21);
				x = temp21;
				return;
			}
		}
		else{
			popLater = true;
		}
		
		//do not create duplicate puzzles and avoid back and forth moves
		//add statement from first if statement that checks if heuristic is equal, to all statements
		if(emptyTileRow == 0 && emptyTileCol == 0 && checkpoint == false){
			//swapRight node and push onto queue
			node* temp1 = new node;
			if(Q.front()->swapMove != "swapLeft"){
				if(!(isRoot && Q.front()->tookRight == true)){
					temp1->puzzle = Q.front()->puzzle;
					swap(temp1->puzzle.at(emptyTileRow).at(emptyTileCol), temp1->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
					Q.front()->swapRight = temp1;
					temp1->parent = Q.front();
					temp1->swapMove = "swapRight";
					temp1->totalMoves = (temp1->parent->totalMoves) + 1;
					temp1->totalMisplacedTiles = findMisplacedTiles(temp1,goal);
					recordParentDirection(temp1, temp1->swapMove);
				}
			}
			//swapBot node and push on to queue
			node* temp2 = new node;
			if(Q.front()->swapMove != "swapTop"){
				if(!(isRoot && Q.front()->tookBot == true)){
					temp2->puzzle = Q.front()->puzzle;
					swap(temp2->puzzle.at(emptyTileRow).at(emptyTileCol), temp2->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
					Q.front()->swapBot = temp2;
					temp2->parent = Q.front();
					temp2->swapMove = "swapBot";
					temp2->totalMoves = (temp2->parent->totalMoves) + 1;
					temp2->totalMisplacedTiles = findMisplacedTiles(temp2,goal);
					recordParentDirection(temp2, temp2->swapMove);
				}
			}
			
			if(temp1->totalMisplacedTiles == temp2->totalMisplacedTiles && (temp1->totalMisplacedTiles > 1)){
				Q.front() = chooseDifferentDirection(Q.front());
				continue;
			}
			
			//calculate and push child with least misplaced tiles
			int value = findMin(temp1->totalMisplacedTiles, temp2->totalMisplacedTiles, 2480, 2480);
			if(value == temp1->totalMisplacedTiles && Q.front()->swapMove != "swapLeft"){
				Q.push(temp1);
			}
			else if(value == temp2->totalMisplacedTiles && Q.front()->swapMove != "swapTop"){
				Q.push(temp2);
			}
		}
		if(emptyTileRow == 0 && emptyTileCol == 1 && checkpoint == false){
			//swapLeft node and push onto queue
			node* temp3 = new node;
			if(Q.front()->swapMove != "swapRight"){
				if(!(isRoot && Q.front()->tookLeft == true)){
					temp3->puzzle = Q.front()->puzzle;
					swap(temp3->puzzle.at(emptyTileRow).at(emptyTileCol), temp3->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp3;
					temp3->parent = Q.front();
					temp3->swapMove = "swapLeft";
					temp3->totalMoves = (temp3->parent->totalMoves) + 1;
					temp3->totalMisplacedTiles = findMisplacedTiles(temp3,goal);
					recordParentDirection(temp3, temp3->swapMove);
				}
			}
			//swapRight node and push onto queue
			node* temp4 = new node;
			if(Q.front()->swapMove != "swapLeft"){
				if(!(isRoot && Q.front()->tookRight == true)){
					temp4->puzzle = Q.front()->puzzle;
					swap(temp4->puzzle.at(emptyTileRow).at(emptyTileCol), temp4->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
					Q.front()->swapRight = temp4;
					temp4->parent = Q.front();
					temp4->swapMove = "swapRight";
					temp4->totalMoves = (temp4->parent->totalMoves) + 1;
					temp4->totalMisplacedTiles = findMisplacedTiles(temp4,goal);
					recordParentDirection(temp4, temp4->swapMove);
				}
			}
			//swapBot node and push on to queue
			node* temp5 = new node;
			if(Q.front()->swapMove != "swapTop"){
				if(!(isRoot && Q.front()->tookBot == true)){
					temp5->puzzle = Q.front()->puzzle;
					swap(temp5->puzzle.at(emptyTileRow).at(emptyTileCol), temp5->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
					Q.front()->swapBot = temp5;
					temp5->parent = Q.front();
					temp5->swapMove = "swapBot";
					temp5->totalMoves = (temp5->parent->totalMoves) + 1;
					temp5->totalMisplacedTiles = findMisplacedTiles(temp5,goal);
					recordParentDirection(temp5, temp5->swapMove);
				}
			}
			
			int value = findMin(temp3->totalMisplacedTiles, temp4->totalMisplacedTiles, temp5->totalMisplacedTiles, 2480);
			if(value == temp3->totalMisplacedTiles && Q.front()->swapMove != "swapRight"){
				Q.push(temp3);
			}
			else if(value == temp4->totalMisplacedTiles && Q.front()->swapMove != "swapLeft"){
				Q.push(temp4);
			}
			else if(value == temp5->totalMisplacedTiles && Q.front()->swapMove != "swapTop"){
				Q.push(temp5);
			}
		}
		if(emptyTileRow == 0 && emptyTileCol == 2 && checkpoint == false){
			//swapLeft node and push onto queue
			node* temp6 = new node;
			if(Q.front()->swapMove != "swapRight"){
				if(!(isRoot && Q.front()->tookLeft == true)){
					temp6->puzzle = Q.front()->puzzle;
					swap(temp6->puzzle.at(emptyTileRow).at(emptyTileCol), temp6->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp6;
					temp6->parent = Q.front();
					temp6->swapMove = "swapLeft";
					temp6->totalMoves = (temp6->parent->totalMoves) + 1;
					temp6->totalMisplacedTiles = findMisplacedTiles(temp6,goal);
					recordParentDirection(temp6, temp6->swapMove);
				}
			}
			//swapBot node and push on to queue
			node* temp7 = new node;
			if(Q.front()->swapMove != "swapTop"){
				if(!(isRoot && Q.front()->tookBot == true)){
					temp7->puzzle = Q.front()->puzzle;
					swap(temp7->puzzle.at(emptyTileRow).at(emptyTileCol), temp7->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
					Q.front()->swapBot = temp7;
					temp7->parent = Q.front();
					temp7->swapMove = "swapBot";
					temp7->totalMoves = (temp7->parent->totalMoves) + 1;
					temp7->totalMisplacedTiles = findMisplacedTiles(temp7,goal);
					recordParentDirection(temp7, temp7->swapMove);
				}
			}
			int value = findMin(temp6->totalMisplacedTiles, temp7->totalMisplacedTiles, 2480, 2480);
			if(value == temp6->totalMisplacedTiles && Q.front()->swapMove != "swapRight"){
				Q.push(temp6);
			}
			if(value == temp7->totalMisplacedTiles && Q.front()->swapMove != "swapTop"){
				Q.push(temp7);
			}
		}
		if(emptyTileRow == 1 && emptyTileCol == 0){
			//swapTop node and push on to queue
			node* temp8 = new node;
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					if(!(isRoot && Q.front()->tookTop == true)){
						temp8->puzzle = Q.front()->puzzle;
						swap(temp8->puzzle.at(emptyTileRow).at(emptyTileCol), temp8->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
						Q.front()->swapTop = temp8;
						temp8->parent = Q.front();
						temp8->swapMove = "swapTop";
						temp8->totalMoves = (temp8->parent->totalMoves) + 1;
						temp8->totalMisplacedTiles = findMisplacedTiles(temp8,goal);
						recordParentDirection(temp8, temp8->swapMove);
					}
				}
			}
			//swapBot node and push on to queue
			node* temp9 = new node;
			if(Q.front()->swapMove != "swapTop"){
				if(!(isRoot && Q.front()->tookBot == true)){
					temp9->puzzle = Q.front()->puzzle;
					swap(temp9->puzzle.at(emptyTileRow).at(emptyTileCol), temp9->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
					Q.front()->swapBot = temp9;
					temp9->parent = Q.front();
					temp9->swapMove = "swapBot";
					temp9->totalMoves = (temp9->parent->totalMoves) + 1;
					temp9->totalMisplacedTiles = findMisplacedTiles(temp9,goal);
					recordParentDirection(temp9, temp9->swapMove);
				}
			}
			//swapRight node and push onto queue
			node* temp10 = new node;
			if(Q.front()->swapMove != "swapLeft"){
				if(!(isRoot && Q.front()->tookRight == true)){
					temp10->puzzle = Q.front()->puzzle;
					swap(temp10->puzzle.at(emptyTileRow).at(emptyTileCol), temp10->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
					Q.front()->swapRight = temp10;
					temp10->parent = Q.front();
					temp10->swapMove = "swapRight";
					temp10->totalMoves = (temp10->parent->totalMoves) + 1;
					temp10->totalMisplacedTiles = findMisplacedTiles(temp10,goal);
					recordParentDirection(temp10, temp10->swapMove);
				}
			}
			
			int value = findMin(temp8->totalMisplacedTiles, temp9->totalMisplacedTiles, temp10->totalMisplacedTiles, 2480);
			if(value == temp8->totalMisplacedTiles && checkpoint == false && Q.front()->swapMove != "swapBot"){
				Q.push(temp8);
			}
			else if(value == temp9->totalMisplacedTiles && Q.front()->swapMove != "swapTop"){
				Q.push(temp9);
			}
			else if(value == temp10->totalMisplacedTiles && Q.front()->swapMove != "swapLeft"){
				Q.push(temp10);
			}
		}
		if(emptyTileRow == 1 && emptyTileCol == 1){
			node* temp11 = new node;
			node* temp12 = new node;
			node* temp13 = new node;
			node* temp14 = new node; 
			//swapTop node and push on to queue
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					if(!(isRoot && Q.front()->tookTop == true)){
						temp11->puzzle = Q.front()->puzzle;
						swap(temp11->puzzle.at(emptyTileRow).at(emptyTileCol), temp11->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
						Q.front()->swapTop = temp11;
						temp11->parent = Q.front();
						temp11->swapMove = "swapTop";
						temp11->totalMoves = (temp11->parent->totalMoves) + 1;
						temp11->totalMisplacedTiles = findMisplacedTiles(temp11,goal);
						recordParentDirection(temp11, temp11->swapMove);
					}
				}
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				if(!(isRoot && Q.front()->tookBot == true)){
					temp12->puzzle = Q.front()->puzzle;
					swap(temp12->puzzle.at(emptyTileRow).at(emptyTileCol), temp12->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
					Q.front()->swapBot = temp12;
					temp12->parent = Q.front();
					temp12->swapMove = "swapBot";
					temp12->totalMoves = (temp12->parent->totalMoves) + 1;
					temp12->totalMisplacedTiles = findMisplacedTiles(temp12,goal);
					recordParentDirection(temp12, temp12->swapMove);
				}
			}
			//swapRight node and push onto queue
			if(Q.front()->swapMove != "swapLeft"){
				if(!(isRoot && Q.front()->tookRight == true)){
					temp13->puzzle = Q.front()->puzzle;
					swap(temp13->puzzle.at(emptyTileRow).at(emptyTileCol), temp13->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
					Q.front()->swapRight = temp13;
					temp13->parent = Q.front();
					temp13->swapMove = "swapRight";
					temp13->totalMoves = (temp13->parent->totalMoves) + 1;
					temp13->totalMisplacedTiles = findMisplacedTiles(temp13,goal);
					recordParentDirection(temp13, temp13->swapMove);
				}
			}
			//swapLeft node and push onto queue
			if(checkpoint2 == false){
				if(Q.front()->swapMove != "swapRight"){
					if(!(isRoot && Q.front()->tookLeft == true)){
						temp14->puzzle = Q.front()->puzzle;
						swap(temp14->puzzle.at(emptyTileRow).at(emptyTileCol), temp14->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
						Q.front()->swapLeft = temp14;
						temp14->parent = Q.front();
						temp14->swapMove = "swapLeft";
						temp14->totalMoves = (temp14->parent->totalMoves) + 1;
						temp14->totalMisplacedTiles = findMisplacedTiles(temp14,goal);
						recordParentDirection(temp14, temp14->swapMove);
					}
				}
			}
			
			int value = findMin(temp11->totalMisplacedTiles, temp12->totalMisplacedTiles, temp13->totalMisplacedTiles, temp14->totalMisplacedTiles); //segfault
			
			if(value == temp11->totalMisplacedTiles && checkpoint == false && Q.front()->swapMove != "swapBot"){
				Q.push(temp11);
			}
			else if(value == temp12->totalMisplacedTiles && Q.front()->swapMove != "swapTop"){
				Q.push(temp12);
			}
			else if(value == temp13->totalMisplacedTiles && Q.front()->swapMove != "swapLeft"){
				Q.push(temp13);
			}
			else if(value == temp14->totalMisplacedTiles && checkpoint2 == false && Q.front()->swapMove != "swapRight"){
				Q.push(temp14);
			}
		}
		if(emptyTileRow == 1 && emptyTileCol == 2){
			//swapTop node and push on to queue
			node* temp15 = new node;
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					if(!(isRoot && Q.front()->tookTop == true)){
						temp15->puzzle = Q.front()->puzzle;
						swap(temp15->puzzle.at(emptyTileRow).at(emptyTileCol), temp15->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
						Q.front()->swapTop = temp15;
						temp15->parent = Q.front();
						temp15->swapMove = "swapTop";
						temp15->totalMoves = (temp15->parent->totalMoves) + 1;
						temp15->totalMisplacedTiles = findMisplacedTiles(temp15,goal);
						recordParentDirection(temp15, temp15->swapMove);
					}
				}
			}
			//swapBot node and push on to queue
			node* temp16 = new node;
			if(Q.front()->swapMove != "swapTop"){
				if(!(isRoot && Q.front()->tookBot == true)){
					temp16->puzzle = Q.front()->puzzle;
					swap(temp16->puzzle.at(emptyTileRow).at(emptyTileCol), temp16->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
					Q.front()->swapBot = temp16;
					temp16->parent = Q.front();
					temp16->swapMove = "swapBot";
					temp16->totalMoves = (temp16->parent->totalMoves) + 1;
					temp16->totalMisplacedTiles = findMisplacedTiles(temp16,goal);
					recordParentDirection(temp16, temp16->swapMove);
				}
			}
			//swapLeft node and push onto queue
			node* temp17 = new node;
			if(Q.front()->swapMove != "swapRight"){
				if(!(isRoot && Q.front()->tookLeft == true)){
					temp17->puzzle = Q.front()->puzzle;
					swap(temp17->puzzle.at(emptyTileRow).at(emptyTileCol), temp17->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp17;
					temp17->parent = Q.front();
					temp17->swapMove = "swapLeft";
					temp17->totalMoves = (temp17->parent->totalMoves) + 1;
					temp17->totalMisplacedTiles = findMisplacedTiles(temp17,goal);
					recordParentDirection(temp17, temp17->swapMove);
				}
			}
			int value = findMin(temp15->totalMisplacedTiles, temp16->totalMisplacedTiles, temp17->totalMisplacedTiles, 2480);
			if(value == temp15->totalMisplacedTiles && checkpoint == false && Q.front()->swapMove != "swapBot"){
				Q.push(temp15);
			}			
			else if(value == temp16->totalMisplacedTiles && Q.front()->swapMove != "swapTop"){
				Q.push(temp16);				
			}			
			else if(value == temp17->totalMisplacedTiles && Q.front()->swapMove != "swapRight"){
				Q.push(temp17);				
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 0){
			//swapTop node and push on to queue
			node* temp18 = new node;
			if(checkpoint2 == false){
				if(Q.front()->swapMove != "swapBot"){
					if(!(isRoot && Q.front()->tookTop == true)){
						temp18->puzzle = Q.front()->puzzle;
						swap(temp18->puzzle.at(emptyTileRow).at(emptyTileCol), temp18->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
						Q.front()->swapTop = temp18;
						temp18->parent = Q.front();
						temp18->swapMove = "swapTop";
						temp18->totalMoves = (temp18->parent->totalMoves) + 1;
						temp18->totalMisplacedTiles = findMisplacedTiles(temp18,goal);
						recordParentDirection(temp18, temp18->swapMove);
					}
				}
			}
			//swapRight node and push onto queue
			node* temp19 = new node;
			if(Q.front()->swapMove != "swapLeft"){
				if(!(isRoot && Q.front()->tookRight == true)){
					temp19->puzzle = Q.front()->puzzle;
					swap(temp19->puzzle.at(emptyTileRow).at(emptyTileCol), temp19->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
					Q.front()->swapRight = temp19;
					temp19->parent = Q.front();
					temp19->swapMove = "swapRight";
					temp19->totalMoves = (temp19->parent->totalMoves) + 1;
					temp19->totalMisplacedTiles = findMisplacedTiles(temp19,goal);
					recordParentDirection(temp19, temp19->swapMove);
				}
			}
			
			int value = findMin(temp18->totalMisplacedTiles, temp19->totalMisplacedTiles, 2480, 2480);
			if(value == temp18->totalMisplacedTiles && checkpoint2 == false && Q.front()->swapMove != "swapBot"){
				Q.push(temp18);
			}
			else if(value == temp19->totalMisplacedTiles && Q.front()->swapMove != "swapLeft"){
				Q.push(temp19);				
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 1){
			//swapTop node and push on to queue
			node* temp20 = new node;
			if(Q.front()->swapMove != "swapBot"){
				if(!(isRoot && Q.front()->tookTop == true)){
					temp20->puzzle = Q.front()->puzzle;
					swap(temp20->puzzle.at(emptyTileRow).at(emptyTileCol), temp20->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp20;
					temp20->parent = Q.front();
					temp20->swapMove = "swapTop";
					temp20->totalMoves = (temp20->parent->totalMoves) + 1;
					temp20->totalMisplacedTiles = findMisplacedTiles(temp20,goal);
					recordParentDirection(temp20, temp20->swapMove);
				}
			}
			//swapRight node and push onto queue
			node* temp21 = new node;
			if(Q.front()->swapMove != "swapLeft"){
				if(!(isRoot && Q.front()->tookRight == true)){
					temp21->puzzle = Q.front()->puzzle;
					swap(temp21->puzzle.at(emptyTileRow).at(emptyTileCol), temp21->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
					Q.front()->swapRight = temp21;
					temp21->parent = Q.front();
					temp21->swapMove = "swapRight";
					temp21->totalMoves = (temp21->parent->totalMoves) + 1;
					temp21->totalMisplacedTiles = findMisplacedTiles(temp21,goal);
					recordParentDirection(temp21, temp21->swapMove);
				}
			}
			//swapLeft node and push onto queue
			node* temp22 = new node;
			if(checkpoint3 == false){
				if(Q.front()->swapMove != "swapRight"){
					if(!(isRoot && Q.front()->tookLeft == true)){
						temp22->puzzle = Q.front()->puzzle;
						swap(temp22->puzzle.at(emptyTileRow).at(emptyTileCol), temp22->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
						Q.front()->swapLeft = temp22;
						temp22->parent = Q.front();
						temp22->swapMove = "swapLeft";
						temp22->totalMoves = (temp22->parent->totalMoves) + 1;
						temp22->totalMisplacedTiles = findMisplacedTiles(temp22,goal);
						recordParentDirection(temp22, temp22->swapMove);
					}
				}
			}
			
			int value = findMin(temp20->totalMisplacedTiles, temp21->totalMisplacedTiles, temp22->totalMisplacedTiles, 2480);
			
			if(value == temp20->totalMisplacedTiles && Q.front()->swapMove != "swapBot"){
				Q.push(temp20);
			}			
			else if(value == temp21->totalMisplacedTiles && Q.front()->swapMove != "swapLeft"){
				Q.push(temp21);
			}			
			else if(value == temp22->totalMisplacedTiles && Q.front()->swapMove != "swapRight"){
				Q.push(temp22);
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 2){
			//swapLeft node and push onto queue
			node* temp23 = new node;
			if(Q.front()->swapMove != "swapRight"){
				if(!(isRoot && Q.front()->tookLeft == true)){
					temp23->puzzle = Q.front()->puzzle;
					swap(temp23->puzzle.at(emptyTileRow).at(emptyTileCol), temp23->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp23;
					temp23->parent = Q.front();
					temp23->swapMove = "swapLeft";
					temp23->totalMoves = (temp23->parent->totalMoves) + 1;
					temp23->totalMisplacedTiles = findMisplacedTiles(temp23,goal);
					recordParentDirection(temp23, temp23->swapMove);
				}
			}
			//swapTop node and push on to queue
			node* temp24 = new node;
			if(Q.front()->swapMove != "swapBot"){
				if(!(isRoot && Q.front()->tookTop == true)){
					temp24->puzzle = Q.front()->puzzle;
					swap(temp24->puzzle.at(emptyTileRow).at(emptyTileCol), temp24->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp24;
					temp24->parent = Q.front();
					temp24->swapMove = "swapTop";
					temp24->totalMoves = (temp24->parent->totalMoves) + 1;
					temp24->totalMisplacedTiles = findMisplacedTiles(temp24,goal);
					recordParentDirection(temp24, temp24->swapMove);
				}
			}
			
			int value = findMin(temp23->totalMisplacedTiles, temp24->totalMisplacedTiles, 2480 , 2480);
			
			if(value == temp23->totalMisplacedTiles && Q.front()->swapMove != "swapRight"){
				Q.push(temp23);
			}			
			else if(value == temp24->totalMisplacedTiles && Q.front()->swapMove != "swapBot"){
				Q.push(temp24);
			}
		}
		if(popLater){
			Q.pop();
		}
	}
	cout << "Leaves while" << endl;
}

#endif