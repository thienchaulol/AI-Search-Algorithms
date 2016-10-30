#ifndef UCS_H_INCLUDED
#define UCS_H_INCLUDED

#include <iostream>
#include <queue>
#include <vector>
#include "treeNode.h"

using namespace std;

//UCS search on root node x
//UCS is done. UCS program is killed when traversing complex puzzles
//but that is the nature of it, it is a long search algorithmm.
void uniformCostSearch(node* &x, node* goal){
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

	//create empty queue of node pointers
	queue<node*> Q;

	//enqueue root node
	//next, enqueue root node's children and check if 
	//children(s) are equal to goal state. if not, enqueue children's
	//children then dequeue original children.
	Q.push(x);
	
	//traverse "tree" by creating nodes that are potential moves
	//if potential state == goal state, exit
	int emptyTileRow = 0;
	int emptyTileCol = 0;
	//int depth = 0; //initial depth
	bool popLater; //bool to pop node after creating it's children
	bool checkpoint = false;
	bool checkpoint2 = false;
	bool checkpoint3 = false;
	while(!Q.empty()){
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
			if(Q.front()->swapMove != "swapLeft"){
				node* temp1 = new node;
				temp1->puzzle = Q.front()->puzzle;
				swap(temp1->puzzle.at(emptyTileRow).at(emptyTileCol), temp1->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp1;
				temp1->parent = Q.front();
				temp1->swapMove = "swapRight";
				temp1->totalMoves = (temp1->parent->totalMoves) + 1;
				Q.push(temp1);
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				node* temp2 = new node;
				temp2->puzzle = Q.front()->puzzle;
				swap(temp2->puzzle.at(emptyTileRow).at(emptyTileCol), temp2->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp2;
				temp2->parent = Q.front();
				temp2->swapMove = "swapBot";
				temp2->totalMoves = (temp2->parent->totalMoves) + 1;
				Q.push(temp2);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 0 && emptyTileCol == 1 && checkpoint == false){
			//swapLeft node and push onto queue
			if(Q.front()->swapMove != "swapRight"){
				node* temp3 = new node;
				temp3->puzzle = Q.front()->puzzle;
				swap(temp3->puzzle.at(emptyTileRow).at(emptyTileCol), temp3->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp3;
				temp3->parent = Q.front();
				temp3->swapMove = "swapLeft";
				temp3->totalMoves = (temp3->parent->totalMoves) + 1;
				Q.push(temp3);
			}
			//swapRight node and push onto queue
			if(Q.front()->swapMove != "swapLeft"){
				node* temp4 = new node;
				temp4->puzzle = Q.front()->puzzle;
				swap(temp4->puzzle.at(emptyTileRow).at(emptyTileCol), temp4->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp4;
				temp4->parent = Q.front();
				temp4->swapMove = "swapRight";
				temp4->totalMoves = (temp4->parent->totalMoves) + 1;
				Q.push(temp4);
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				node* temp5 = new node;
				temp5->puzzle = Q.front()->puzzle;
				swap(temp5->puzzle.at(emptyTileRow).at(emptyTileCol), temp5->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp5;
				temp5->parent = Q.front();
				temp5->swapMove = "swapBot";
				temp5->totalMoves = (temp5->parent->totalMoves) + 1;
				Q.push(temp5);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 0 && emptyTileCol == 2 && checkpoint == false){
			//swapLeft node and push onto queue
			if(Q.front()->swapMove != "swapRight"){
				node* temp6 = new node;
				temp6->puzzle = Q.front()->puzzle;
				swap(temp6->puzzle.at(emptyTileRow).at(emptyTileCol), temp6->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp6;
				temp6->parent = Q.front();
				temp6->swapMove = "swapLeft";
				temp6->totalMoves = (temp6->parent->totalMoves) + 1;
				Q.push(temp6);
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				node* temp7 = new node;
				temp7->puzzle = Q.front()->puzzle;
				swap(temp7->puzzle.at(emptyTileRow).at(emptyTileCol), temp7->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp7;
				temp7->parent = Q.front();
				temp7->swapMove = "swapBot";
				temp7->totalMoves = (temp7->parent->totalMoves) + 1;
				Q.push(temp7);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 1 && emptyTileCol == 0){
			//swapTop node and push on to queue
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					node* temp8 = new node;
					temp8->puzzle = Q.front()->puzzle;
					swap(temp8->puzzle.at(emptyTileRow).at(emptyTileCol), temp8->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp8;
					temp8->parent = Q.front();
					temp8->swapMove = "swapTop";
					temp8->totalMoves = (temp8->parent->totalMoves) + 1;
					Q.push(temp8);
				}
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				node* temp9 = new node;
				temp9->puzzle = Q.front()->puzzle;
				swap(temp9->puzzle.at(emptyTileRow).at(emptyTileCol), temp9->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp9;
				temp9->parent = Q.front();
				temp9->swapMove = "swapBot";
				temp9->totalMoves = (temp9->parent->totalMoves) + 1;
				Q.push(temp9);
			}
			//swapRight node and push onto queue
			if(Q.front()->swapMove != "swapLeft"){
				node* temp10 = new node;
				temp10->puzzle = Q.front()->puzzle;
				swap(temp10->puzzle.at(emptyTileRow).at(emptyTileCol), temp10->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp10;
				temp10->parent = Q.front();
				temp10->swapMove = "swapRight";
				temp10->totalMoves = (temp10->parent->totalMoves) + 1;
				Q.push(temp10);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 1 && emptyTileCol == 1){
			//swapTop node and push on to queue
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					node* temp11 = new node;
					temp11->puzzle = Q.front()->puzzle;
					swap(temp11->puzzle.at(emptyTileRow).at(emptyTileCol), temp11->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp11;
					temp11->parent = Q.front();
					temp11->swapMove = "swapTop";
					temp11->totalMoves = (temp11->parent->totalMoves) + 1;
					Q.push(temp11);
				}
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				node* temp12 = new node;
				temp12->puzzle = Q.front()->puzzle;
				swap(temp12->puzzle.at(emptyTileRow).at(emptyTileCol), temp12->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp12;
				temp12->parent = Q.front();
				temp12->swapMove = "swapBot";
				temp12->totalMoves = (temp12->parent->totalMoves) + 1;
				Q.push(temp12);
			}
			//swapRight node and push onto queue
			if(Q.front()->swapMove != "swapLeft"){
				node* temp13 = new node;
				temp13->puzzle = Q.front()->puzzle;
				swap(temp13->puzzle.at(emptyTileRow).at(emptyTileCol), temp13->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp13;
				temp13->parent = Q.front();
				temp13->swapMove = "swapRight";
				temp13->totalMoves = (temp13->parent->totalMoves) + 1;
				Q.push(temp13);
			}
			//swapLeft node and push onto queue
			if(checkpoint2 == false){
				if(Q.front()->swapMove != "swapRight"){
					node* temp14 = new node;
					temp14->puzzle = Q.front()->puzzle;
					swap(temp14->puzzle.at(emptyTileRow).at(emptyTileCol), temp14->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp14;
					temp14->parent = Q.front();
					temp14->swapMove = "swapLeft";
					temp14->totalMoves = (temp14->parent->totalMoves) + 1;
					Q.push(temp14);
				}
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 1 && emptyTileCol == 2){
			//swapTop node and push on to queue
			if(checkpoint == false){
				if(Q.front()->swapMove != "swapBot"){
					node* temp15 = new node;
					temp15->puzzle = Q.front()->puzzle;
					swap(temp15->puzzle.at(emptyTileRow).at(emptyTileCol), temp15->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp15;
					temp15->parent = Q.front();
					temp15->swapMove = "swapTop";
					temp15->totalMoves = (temp15->parent->totalMoves) + 1;
					Q.push(temp15);
				}
			}
			//swapBot node and push on to queue
			if(Q.front()->swapMove != "swapTop"){
				node* temp16 = new node;
				temp16->puzzle = Q.front()->puzzle;
				swap(temp16->puzzle.at(emptyTileRow).at(emptyTileCol), temp16->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
				Q.front()->swapBot = temp16;
				temp16->parent = Q.front();
				temp16->swapMove = "swapBot";
				temp16->totalMoves = (temp16->parent->totalMoves) + 1;
				Q.push(temp16);
			}
			//swapLeft node and push onto queue
			if(Q.front()->swapMove != "swapRight"){
				node* temp17 = new node;
				temp17->puzzle = Q.front()->puzzle;
				swap(temp17->puzzle.at(emptyTileRow).at(emptyTileCol), temp17->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp17;
				temp17->parent = Q.front();
				temp17->swapMove = "swapLeft";
				temp17->totalMoves = (temp17->parent->totalMoves) + 1;
				Q.push(temp17);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 2 && emptyTileCol == 0){
			//swapTop node and push on to queue
			if(checkpoint2 == false){
				if(Q.front()->swapMove != "swapBot"){
					node* temp18 = new node;
					temp18->puzzle = Q.front()->puzzle;
					swap(temp18->puzzle.at(emptyTileRow).at(emptyTileCol), temp18->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
					Q.front()->swapTop = temp18;
					temp18->parent = Q.front();
					temp18->swapMove = "swapTop";
					temp18->totalMoves = (temp18->parent->totalMoves) + 1;
					Q.push(temp18);
				}
			}
			//swapRight node and push onto queue
			if(Q.front()->swapMove != "swapLeft"){
				node* temp19 = new node;
				temp19->puzzle = Q.front()->puzzle;
				swap(temp19->puzzle.at(emptyTileRow).at(emptyTileCol), temp19->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp19;
				temp19->parent = Q.front();
				temp19->swapMove = "swapRight";
				temp19->totalMoves = (temp19->parent->totalMoves) + 1;
				Q.push(temp19);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 2 && emptyTileCol == 1){
			//swapTop node and push on to queue
			if(Q.front()->swapMove != "swapBot"){
				node* temp20 = new node;
				temp20->puzzle = Q.front()->puzzle;
				swap(temp20->puzzle.at(emptyTileRow).at(emptyTileCol), temp20->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp20;
				temp20->parent = Q.front();
				temp20->swapMove = "swapTop";
				temp20->totalMoves = (temp20->parent->totalMoves) + 1;
				Q.push(temp20);
			}
			//swapRight node and push onto queue
			if(Q.front()->swapMove != "swapLeft"){
				node* temp21 = new node;
				temp21->puzzle = Q.front()->puzzle;
				swap(temp21->puzzle.at(emptyTileRow).at(emptyTileCol), temp21->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
				Q.front()->swapRight = temp21;
				temp21->parent = Q.front();
				temp21->swapMove = "swapRight";
				temp21->totalMoves = (temp21->parent->totalMoves) + 1;
				Q.push(temp21);
			}
			//swapLeft node and push onto queue
			if(checkpoint3 == false){
				if(Q.front()->swapMove != "swapRight"){
					node* temp22 = new node;
					temp22->puzzle = Q.front()->puzzle;
					swap(temp22->puzzle.at(emptyTileRow).at(emptyTileCol), temp22->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
					Q.front()->swapLeft = temp22;
					temp22->parent = Q.front();
					temp22->swapMove = "swapLeft";
					temp22->totalMoves = (temp22->parent->totalMoves) + 1;
					Q.push(temp22);
				}
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 2 && emptyTileCol == 2){
			//swapLeft node and push onto queue
			if(Q.front()->swapMove != "swapRight"){
				node* temp23 = new node;
				temp23->puzzle = Q.front()->puzzle;
				swap(temp23->puzzle.at(emptyTileRow).at(emptyTileCol), temp23->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp23;
				temp23->parent = Q.front();
				temp23->swapMove = "swapLeft";
				temp23->totalMoves = (temp23->parent->totalMoves) + 1;
				Q.push(temp23);
			}
			//swapTop node and push on to queue
			if(Q.front()->swapMove != "swapBot"){
				node* temp24 = new node;
				temp24->puzzle = Q.front()->puzzle;
				swap(temp24->puzzle.at(emptyTileRow).at(emptyTileCol), temp24->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp24;
				temp24->parent = Q.front();
				temp24->swapMove = "swapTop";
				temp24->totalMoves = (temp24->parent->totalMoves) + 1;
				Q.push(temp24);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(popLater){
			Q.pop();
		}
	}
	cout << "Leaves while" << endl;
}

#endif