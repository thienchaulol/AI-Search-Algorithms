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
            if(x->puzzle.at(i).at(j) != goal->puzzle.at(i).at(j)){
                totalMisplacedTiles++;
            }
        }
    }
    return totalMisplacedTiles;
}

int findMin(int w, int x, int y, int z){
	vector<int> temp;
	temp.push_back(w);
	temp.push_back(x);
	temp.push_back(y);
	temp.push_back(z);
	int lowest = 10;
	for(int i = 0; i < temp.size(); i++){
		if(temp.at(i) <= lowest){
			lowest = temp.at(i);
		}
	}
	return lowest;
}

//UCS search on root node x
//GETS KILLED ON COMPLEX 8 PUZZLES
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
		cout << "puzzles are equal; return\n";
		return;
	} else {
		cout << "puzzles are not equal; search \n";
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
	
	queue< node* > Q;
	Q.push(x);
	
	vector<int> totalMisplacedTilesVector;

	while(!Q.empty()){
		//10.29.16 6:01 PM
		//	have a queue. push the child with the lowest misplaced tiles onto queue, pop parent
		//	loop until find solution
		//	if the lowest misplaced tiles are the same, choose one at random or leftmost(doesn't matter)
		//	if you get stuck, get it to function first before perfecting it(professor's words)
		//
		//	at the end of every if statement, only push the node that has more misplaced tiles
		//		compare the totalMisplacedTiles of all children
		
		//check if puzzle is solvable
		if(solvable(Q.front()) == false){
			cout << "Error: Puzzle is not solvable" << endl;
			return;
		}

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
		
		// //check if totalmoves exceed 8 puzzle diameter
		// if(Q.front()->totalMoves >= 31){	//if the Q.front()->totalMoves is equal to 32 or greater, pop Q.front
		// 	Q.pop();
		// 	popLater = false; //skip rest of while loop
		// }

		//do not create duplicate puzzles and avoid back and forth moves
		if(emptyTileRow == 0 && emptyTileCol == 0 && checkpoint == false){
			//swapRight node and push onto queue
			node* temp1;
			if(Q.front()->swapMove != "swapLeft"){
				temp1 = new node;
				temp1->puzzle = Q.front()->puzzle;
				swap(temp1->puzzle.at(emptyTileRow).at(emptyTileCol), temp1->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp1;
				temp1->parent = Q.front();
				temp1->swapMove = "swapRight";
				temp1->totalMoves = (temp1->parent->totalMoves) + 1;
			}
			//swapBot node and push on to queue
			node* temp2;
			if(Q.front()->swapMove != "swapTop"){
				temp2 = new node;
				temp2->puzzle = Q.front()->puzzle;
				swap(temp2->puzzle.at(emptyTileRow).at(emptyTileCol), temp2->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp2;
				temp2->parent = Q.front();
				temp2->swapMove = "swapBot";
				temp2->totalMoves = (temp2->parent->totalMoves) + 1;
			}
			//calculate and push child with least misplaced tiles
			int temp1MPT = findMisplacedTiles(temp1, goal);
			int temp2MPT = findMisplacedTiles(temp2, goal);
			
			int value = findMin(temp1MPT, temp2MPT, 10, 10);
			
			if(value == temp1MPT){
				Q.push(temp1);
			}
			else if(value == temp2MPT){
				Q.push(temp2);
			}
		}
		if(emptyTileRow == 0 && emptyTileCol == 1 && checkpoint == false){
			//swapLeft node and push onto queue
			node* temp3;
			if(Q.front()->swapMove != "swapRight"){
				temp3 = new node;
				temp3->puzzle = Q.front()->puzzle;
				swap(temp3->puzzle.at(emptyTileRow).at(emptyTileCol), temp3->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp3;
				temp3->parent = Q.front();
				temp3->swapMove = "swapLeft";
				temp3->totalMoves = (temp3->parent->totalMoves) + 1;
			}
			//swapRight node and push onto queue
			node* temp4;
			if(Q.front()->swapMove != "swapLeft"){
				temp4 = new node;
				temp4->puzzle = Q.front()->puzzle;
				swap(temp4->puzzle.at(emptyTileRow).at(emptyTileCol), temp4->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp4;
				temp4->parent = Q.front();
				temp4->swapMove = "swapRight";
				temp4->totalMoves = (temp4->parent->totalMoves) + 1;
			}
			//swapBot node and push on to queue
			node* temp5;
			if(Q.front()->swapMove != "swapTop"){
				temp5 = new node;
				temp5->puzzle = Q.front()->puzzle;
				swap(temp5->puzzle.at(emptyTileRow).at(emptyTileCol), temp5->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp5;
				temp5->parent = Q.front();
				temp5->swapMove = "swapBot";
				temp5->totalMoves = (temp5->parent->totalMoves) + 1;
			}
			//calculate and push child with least misplaced tiles
			int temp3MPT = findMisplacedTiles(temp3, goal);
			int temp4MPT = findMisplacedTiles(temp4, goal);
			int temp5MPT = findMisplacedTiles(temp5, goal);
			
			int value = findMin(temp3MPT, temp4MPT, temp5MPT, 10);
			if(value == temp3MPT){
				Q.push(temp3);
			}
			else if(value == temp4MPT){
				Q.push(temp4);
			}
			else if(value == temp5MPT){
				Q.push(temp5);
			}
		}
		if(emptyTileRow == 0 && emptyTileCol == 2 && checkpoint == false){
			//swapLeft node and push onto queue
			node* temp6;
			if(Q.front()->swapMove != "swapRight"){
				temp6 = new node;
				temp6->puzzle = Q.front()->puzzle;
				swap(temp6->puzzle.at(emptyTileRow).at(emptyTileCol), temp6->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp6;
				temp6->parent = Q.front();
				temp6->swapMove = "swapLeft";
				temp6->totalMoves = (temp6->parent->totalMoves) + 1;
			}
			//swapBot node and push on to queue
			node* temp7;
			if(Q.front()->swapMove != "swapTop"){
				temp7 = new node;
				temp7->puzzle = Q.front()->puzzle;
				swap(temp7->puzzle.at(emptyTileRow).at(emptyTileCol), temp7->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp7;
				temp7->parent = Q.front();
				temp7->swapMove = "swapBot";
				temp7->totalMoves = (temp7->parent->totalMoves) + 1;
			}
			//calculate and push child with least misplaced tiles
			int temp6MPT = findMisplacedTiles(temp6, goal);
			int temp7MPT = findMisplacedTiles(temp7, goal);
			
			int value = findMin(temp6MPT, temp7MPT, 10, 10);
			if(value == temp6MPT){
				Q.push(temp6);
			}
			else if(value == temp7MPT){
				Q.push(temp7);
			}
			
		}
		if(emptyTileRow == 1 && emptyTileCol == 0){
			//swapTop node and push on to queue
			node* temp8;
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					temp8 = new node;
					temp8->puzzle = Q.front()->puzzle;
					swap(temp8->puzzle.at(emptyTileRow).at(emptyTileCol), temp8->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp8;
					temp8->parent = Q.front();
					temp8->swapMove = "swapTop";
					temp8->totalMoves = (temp8->parent->totalMoves) + 1;
				}
			}
			//swapBot node and push on to queue
			node* temp9;
			if(Q.front()->swapMove != "swapTop"){
				temp9 = new node;
				temp9->puzzle = Q.front()->puzzle;
				swap(temp9->puzzle.at(emptyTileRow).at(emptyTileCol), temp9->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp9;
				temp9->parent = Q.front();
				temp9->swapMove = "swapBot";
				temp9->totalMoves = (temp9->parent->totalMoves) + 1;
			}
			//swapRight node and push onto queue
			node* temp10;
			if(Q.front()->swapMove != "swapLeft"){
				temp10 = new node;
				temp10->puzzle = Q.front()->puzzle;
				swap(temp10->puzzle.at(emptyTileRow).at(emptyTileCol), temp10->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp10;
				temp10->parent = Q.front();
				temp10->swapMove = "swapRight";
				temp10->totalMoves = (temp10->parent->totalMoves) + 1;
			}
			int temp8MPT = findMisplacedTiles(temp8, goal);
			int temp9MPT = findMisplacedTiles(temp9, goal);
			int temp10MPT = findMisplacedTiles(temp10, goal);
			
			int value = findMin(temp8MPT, temp9MPT, temp10MPT, 10);
			if(value == temp8MPT){
				Q.push(temp8);
			}
			else if(value == temp9MPT){
				Q.push(temp9);
			}
			else if(value == temp10MPT){
				Q.push(temp10);
			}
		}
		if(emptyTileRow == 1 && emptyTileCol == 1){
			//swapTop node and push on to queue
			node* temp11;
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					temp11 = new node;
					temp11->puzzle = Q.front()->puzzle;
					swap(temp11->puzzle.at(emptyTileRow).at(emptyTileCol), temp11->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp11;
					temp11->parent = Q.front();
					temp11->swapMove = "swapTop";
					temp11->totalMoves = (temp11->parent->totalMoves) + 1;
				}
			}
			//swapBot node and push on to queue
			node* temp12;
			if(Q.front()->swapMove != "swapTop"){
				temp12 = new node;
				temp12->puzzle = Q.front()->puzzle;
				swap(temp12->puzzle.at(emptyTileRow).at(emptyTileCol), temp12->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp12;
				temp12->parent = Q.front();
				temp12->swapMove = "swapBot";
				temp12->totalMoves = (temp12->parent->totalMoves) + 1;
			}
			//swapRight node and push onto queue
			node* temp13;
			if(Q.front()->swapMove != "swapLeft"){
				temp13 = new node;
				temp13->puzzle = Q.front()->puzzle;
				swap(temp13->puzzle.at(emptyTileRow).at(emptyTileCol), temp13->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp13;
				temp13->parent = Q.front();
				temp13->swapMove = "swapRight";
				temp13->totalMoves = (temp13->parent->totalMoves) + 1;
			}
			//swapLeft node and push onto queue
			node* temp14;
			if(checkpoint2 == false){
				if(Q.front()->swapMove != "swapRight"){
					temp14 = new node;
					temp14->puzzle = Q.front()->puzzle;
					swap(temp14->puzzle.at(emptyTileRow).at(emptyTileCol), temp14->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp14;
					temp14->parent = Q.front();
					temp14->swapMove = "swapLeft";
					temp14->totalMoves = (temp14->parent->totalMoves) + 1;
				}
			}
			
			int temp11MPT = findMisplacedTiles(temp11, goal);
			int temp12MPT = findMisplacedTiles(temp12, goal);
			int temp13MPT = findMisplacedTiles(temp13, goal);
			int temp14MPT = findMisplacedTiles(temp14, goal);
			
			// cout << "temp11" << temp11MPT << endl;
			// cout << "temp12" << temp12MPT << endl;
			// cout << "temp13" << temp13MPT << endl;
			// cout << "temp14" << temp14MPT << endl;
			
			int value = findMin(temp11MPT, temp12MPT, temp13MPT, temp14MPT);
			
			// cout << "value" << value << endl;
			
			if(value == temp11MPT){
				Q.push(temp11);
			}
			else if(value == temp12MPT){
				Q.push(temp12);
			}
			else if(value == temp13MPT){
				Q.push(temp13);
			}
			else if(value == temp14MPT){
				Q.push(temp14);
			}
		}
		if(emptyTileRow == 1 && emptyTileCol == 2){
			//swapTop node and push on to queue
			node* temp15;
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					temp15 = new node;
					temp15->puzzle = Q.front()->puzzle;
					swap(temp15->puzzle.at(emptyTileRow).at(emptyTileCol), temp15->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp15;
					temp15->parent = Q.front();
					temp15->swapMove = "swapTop";
					temp15->totalMoves = (temp15->parent->totalMoves) + 1;
				}
			}
			//swapBot node and push on to queue
			node* temp16;
			if(Q.front()->swapMove != "swapTop"){
				temp16 = new node;
				temp16->puzzle = Q.front()->puzzle;
				swap(temp16->puzzle.at(emptyTileRow).at(emptyTileCol), temp16->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp16;
				temp16->parent = Q.front();
				temp16->swapMove = "swapBot";
				temp16->totalMoves = (temp16->parent->totalMoves) + 1;
			}
			//swapLeft node and push onto queue
			node* temp17;
			if(Q.front()->swapMove != "swapRight"){
				temp17 = new node;
				temp17->puzzle = Q.front()->puzzle;
				swap(temp17->puzzle.at(emptyTileRow).at(emptyTileCol), temp17->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp17;
				temp17->parent = Q.front();
				temp17->swapMove = "swapLeft";
				temp17->totalMoves = (temp17->parent->totalMoves) + 1;
			}
			
			int temp15MPT = findMisplacedTiles(temp15, goal);
			int temp16MPT = findMisplacedTiles(temp16, goal);
			int temp17MPT = findMisplacedTiles(temp17, goal);
			
			int value = findMin(temp15MPT, temp16MPT, temp17MPT, 10);
			
			if(value == temp15MPT){
				Q.push(temp15);
			}			
			else if(value == temp16MPT){
				Q.push(temp16);				
			}			
			else if(value == temp17MPT){
				Q.push(temp17);				
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 0){
			//swapTop node and push on to queue
			node* temp18;
			if(checkpoint2 == false){
				if(Q.front()->swapMove != "swapBot"){
					temp18 = new node;
					temp18->puzzle = Q.front()->puzzle;
					swap(temp18->puzzle.at(emptyTileRow).at(emptyTileCol), temp18->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp18;
					temp18->parent = Q.front();
					temp18->swapMove = "swapTop";
					temp18->totalMoves = (temp18->parent->totalMoves) + 1;
				}
			}
			//swapRight node and push onto queue
			node* temp19;
			if(Q.front()->swapMove != "swapLeft"){
				temp19 = new node;
				temp19->puzzle = Q.front()->puzzle;
				swap(temp19->puzzle.at(emptyTileRow).at(emptyTileCol), temp19->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp19;
				temp19->parent = Q.front();
				temp19->swapMove = "swapRight";
				temp19->totalMoves = (temp19->parent->totalMoves) + 1;
			}
			
			int temp18MPT = findMisplacedTiles(temp18, goal);
			int temp19MPT = findMisplacedTiles(temp19, goal);
			
			int value = findMin(temp18MPT, temp19MPT, 10, 10);
			if(value == temp18MPT){
				Q.push(temp18);
			}
			else if(value == temp19MPT){
				Q.push(temp19);				
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 1){
			//swapTop node and push on to queue
			node* temp20;
			if(Q.front()->swapMove != "swapBot"){
				temp20 = new node;
				temp20->puzzle = Q.front()->puzzle;
				swap(temp20->puzzle.at(emptyTileRow).at(emptyTileCol), temp20->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp20;
				temp20->parent = Q.front();
				temp20->swapMove = "swapTop";
				temp20->totalMoves = (temp20->parent->totalMoves) + 1;
			}
			//swapRight node and push onto queue
			node* temp21;
			if(Q.front()->swapMove != "swapLeft"){
				temp21 = new node;
				temp21->puzzle = Q.front()->puzzle;
				swap(temp21->puzzle.at(emptyTileRow).at(emptyTileCol), temp21->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp21;
				temp21->parent = Q.front();
				temp21->swapMove = "swapRight";
				temp21->totalMoves = (temp21->parent->totalMoves) + 1;
			}
			//swapLeft node and push onto queue
			node* temp22;
			if(checkpoint3 == false){
				if(Q.front()->swapMove != "swapRight"){
					temp22 = new node;
					temp22->puzzle = Q.front()->puzzle;
					swap(temp22->puzzle.at(emptyTileRow).at(emptyTileCol), temp22->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp22;
					temp22->parent = Q.front();
					temp22->swapMove = "swapLeft";
					temp22->totalMoves = (temp22->parent->totalMoves) + 1;
				}
			}
			
			int temp20MPT = findMisplacedTiles(temp20, goal);
			int temp21MPT = findMisplacedTiles(temp21, goal);
			int temp22MPT = findMisplacedTiles(temp22, goal);
			
			int value = findMin(temp20MPT, temp21MPT, temp22MPT, 10);
			
			if(value == temp20MPT){
				Q.push(temp20);
			}			
			else if(value == temp21MPT){
				Q.push(temp21);
			}			
			else if(value == temp22MPT){
				Q.push(temp22);
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 2){
			//swapLeft node and push onto queue
			node* temp23;
			if(Q.front()->swapMove != "swapRight"){
				temp23 = new node;
				temp23->puzzle = Q.front()->puzzle;
				swap(temp23->puzzle.at(emptyTileRow).at(emptyTileCol), temp23->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp23;
				temp23->parent = Q.front();
				temp23->swapMove = "swapLeft";
				temp23->totalMoves = (temp23->parent->totalMoves) + 1;
			}
			//swapTop node and push on to queue
			node* temp24;
			if(Q.front()->swapMove != "swapBot"){
				temp24 = new node;
				temp24->puzzle = Q.front()->puzzle;
				swap(temp24->puzzle.at(emptyTileRow).at(emptyTileCol), temp24->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp24;
				temp24->parent = Q.front();
				temp24->swapMove = "swapTop";
				temp24->totalMoves = (temp24->parent->totalMoves) + 1;
			}
			
			int temp23MPT = findMisplacedTiles(temp23, goal);
			int temp24MPT = findMisplacedTiles(temp24, goal);
			
			int value = findMin(temp23MPT, temp24MPT, 10 , 10);
			
			if(value == temp23MPT){
				Q.push(temp23);
			}			
			else if(value == temp24MPT){
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