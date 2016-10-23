#ifndef UCS_H_INCLUDED
#define UCS_H_INCLUDED

#include <iostream>
#include <queue>
#include <vector>
#include "treeNode.h"

using namespace std;

//UCS search on root node x
//GETS KILLED ON COMPLEX 8 PUZZLES
void uniformCostSearch(node* &x, node* goal){
	//check if user puzzle is equal to goal puzzle
	if(x->puzzle == goal->puzzle){
		cout << "puzzles are equal; return\n";
		return;
	} else {
		cout << "puzzles are not equal; search \n";
	}

	//create empty queue of node pointers
	queue<node*> Q;

	//enqueue root node
	//next, enqueue root node's children and check if 
	//children(s) are equal to goal state. if not, enqueue children's
	//children then dequeue original children.
	Q.push(x);
	x->parent = NULL;
	
	//traverse "tree" by creating nodes that are potential moves
	//if potential state == goal state, exit
	int emptyTileRow = 0;
	int emptyTileCol = 0;
	//int depth = 0; //initial depth
	bool popLater; //bool to pop node after creating it's children
	bool checkpoint = false;
	bool checkpoint2 = false;
	bool checkpoint3 = false;
	while(!Q.empty() /*&& x->puzzle != goal->puzzle*/){	
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
		if(Q.front()->puzzle.at(0).at(0) == 1 && Q.front()->puzzle.at(0).at(1) == 2 && Q.front()->puzzle.at(0).at(2) == 3 
			&& Q.front()->puzzle.at(1).at(0) == 4 && checkpoint3 == false){
			checkpoint2 = true;
		}
		if(Q.front()->puzzle.at(0).at(0) == 1 && Q.front()->puzzle.at(0).at(1) == 2 && Q.front()->puzzle.at(0).at(2) == 3 
			&& Q.front()->puzzle.at(1).at(0) == 4 && Q.front()->puzzle.at(2).at(0) == 7){
			checkpoint3 = true;
		}

		popLater = false;
		if(Q.front()->puzzle == goal->puzzle){
			cout << "PUZZLE FOUND; exit" << endl;
			x = Q.front();	//set original node to solution node
			return;
		}
		else{
			popLater = true;
		}

		//do not create duplicate puzzles
		if(emptyTileRow == 0 && emptyTileCol == 0 && checkpoint == false){
			//swapRight node and push onto queue
			node* temp1 = new node;
			temp1->puzzle = Q.front()->puzzle;
			swap(temp1->puzzle.at(emptyTileRow).at(emptyTileCol), temp1->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			Q.front()->swapRight = temp1;
			temp1->parent = Q.front();
			Q.push(temp1);
			//swapBot node and push on to queue
			node* temp2 = new node;
			temp2->puzzle = Q.front()->puzzle;
			swap(temp2->puzzle.at(emptyTileRow).at(emptyTileCol), temp2->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			Q.front()->swapBot = temp2;
			temp2->parent = Q.front();
			Q.push(temp2);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 0 && emptyTileCol == 1 && checkpoint == false){
			//swapLeft node and push onto queue
			node* temp3 = new node;
			temp3->puzzle = Q.front()->puzzle;
			swap(temp3->puzzle.at(emptyTileRow).at(emptyTileCol), temp3->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			Q.front()->swapLeft = temp3;
			temp3->parent = Q.front();
			Q.push(temp3);
			//swapRight node and push onto queue
			node* temp4 = new node;
			temp4->puzzle = Q.front()->puzzle;
			swap(temp4->puzzle.at(emptyTileRow).at(emptyTileCol), temp4->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			Q.front()->swapRight = temp4;
			temp4->parent = Q.front();
			Q.push(temp4);
			//swapBot node and push on to queue
			node* temp5 = new node;
			temp5->puzzle = Q.front()->puzzle;
			swap(temp5->puzzle.at(emptyTileRow).at(emptyTileCol), temp5->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			Q.front()->swapBot = temp5;
			temp5->parent = Q.front();
			Q.push(temp5);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 0 && emptyTileCol == 2 && checkpoint == false){
			//swapLeft node and push onto queue
			node* temp6 = new node;
			temp6->puzzle = Q.front()->puzzle;
			swap(temp6->puzzle.at(emptyTileRow).at(emptyTileCol), temp6->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			Q.front()->swapLeft = temp6;
			temp6->parent = Q.front();
			Q.push(temp6);
			//swapBot node and push on to queue
			node* temp7 = new node;
			temp7->puzzle = Q.front()->puzzle;
			swap(temp7->puzzle.at(emptyTileRow).at(emptyTileCol), temp7->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			Q.front()->swapBot = temp7;
			temp7->parent = Q.front();
			Q.push(temp7);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 1 && emptyTileCol == 0){
			//swapTop node and push on to queue
			if(checkpoint == false){
				node* temp8 = new node;
				temp8->puzzle = Q.front()->puzzle;
				swap(temp8->puzzle.at(emptyTileRow).at(emptyTileCol), temp8->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp8;
				temp8->parent = Q.front();
				Q.push(temp8);
			}
			//swapBot node and push on to queue
			node* temp9 = new node;
			temp9->puzzle = Q.front()->puzzle;
			swap(temp9->puzzle.at(emptyTileRow).at(emptyTileCol), temp9->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			Q.front()->swapBot = temp9;
			temp9->parent = Q.front();
			Q.push(temp9);
			//swapRight node and push onto queue
			node* temp10 = new node;
			temp10->puzzle = Q.front()->puzzle;
			swap(temp10->puzzle.at(emptyTileRow).at(emptyTileCol), temp10->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			Q.front()->swapRight = temp10;
			temp10->parent = Q.front();
			Q.push(temp10);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 1 && emptyTileCol == 1){
			//swapTop node and push on to queue
			if(checkpoint == false){
				node* temp11 = new node;
				temp11->puzzle = Q.front()->puzzle;
				swap(temp11->puzzle.at(emptyTileRow).at(emptyTileCol), temp11->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp11;
				temp11->parent = Q.front();
				Q.push(temp11);
			}
			//swapBot node and push on to queue
			node* temp12 = new node;
			temp12->puzzle = Q.front()->puzzle;
			swap(temp12->puzzle.at(emptyTileRow).at(emptyTileCol), temp12->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			Q.front()->swapBot = temp12;
			temp12->parent = Q.front();
			Q.push(temp12);
			//swapRight node and push onto queue
			node* temp13 = new node;
			temp13->puzzle = Q.front()->puzzle;
			swap(temp13->puzzle.at(emptyTileRow).at(emptyTileCol), temp13->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			Q.front()->swapRight = temp13;
			temp13->parent = Q.front();
			Q.push(temp13);
			//swapLeft node and push onto queue
			if(checkpoint2 == false){
				node* temp14 = new node;
				temp14->puzzle = Q.front()->puzzle;
				swap(temp14->puzzle.at(emptyTileRow).at(emptyTileCol), temp14->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp14;
				temp14->parent = Q.front();
				Q.push(temp14);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 1 && emptyTileCol == 2){
			//swapTop node and push on to queue
			if(checkpoint == false){
				node* temp15 = new node;
				temp15->puzzle = Q.front()->puzzle;
				swap(temp15->puzzle.at(emptyTileRow).at(emptyTileCol), temp15->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp15;
				temp15->parent = Q.front();
				Q.push(temp15);
			}
			//swapBot node and push on to queue
			node* temp16 = new node;
			temp16->puzzle = Q.front()->puzzle;
			swap(temp16->puzzle.at(emptyTileRow).at(emptyTileCol), temp16->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			Q.front()->swapBot = temp16;
			temp16->parent = Q.front();
			Q.push(temp16);
			//swapLeft node and push onto queue
			node* temp17 = new node;
			temp17->puzzle = Q.front()->puzzle;
			swap(temp17->puzzle.at(emptyTileRow).at(emptyTileCol), temp17->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			Q.front()->swapLeft = temp17;
			temp17->parent = Q.front();
			Q.push(temp17);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 2 && emptyTileCol == 0){
			//swapTop node and push on to queue
			if(checkpoint2 == false){
				node* temp18 = new node;
				temp18->puzzle = Q.front()->puzzle;
				swap(temp18->puzzle.at(emptyTileRow).at(emptyTileCol), temp18->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
				Q.front()->swapTop = temp18;
				temp18->parent = Q.front();
				Q.push(temp18);
			}
			//swapRight node and push onto queue
			node* temp19 = new node;
			temp19->puzzle = Q.front()->puzzle;
			swap(temp19->puzzle.at(emptyTileRow).at(emptyTileCol), temp19->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			Q.front()->swapRight = temp19;
			temp19->parent = Q.front();
			Q.push(temp19);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 2 && emptyTileCol == 1){
			//swapTop node and push on to queue
			node* temp20 = new node;
			temp20->puzzle = Q.front()->puzzle;
			swap(temp20->puzzle.at(emptyTileRow).at(emptyTileCol), temp20->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			Q.front()->swapTop = temp20;
			temp20->parent = Q.front();
			Q.push(temp20);
			//swapRight node and push onto queue
			node* temp21 = new node;
			temp21->puzzle = Q.front()->puzzle;
			swap(temp21->puzzle.at(emptyTileRow).at(emptyTileCol), temp21->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			Q.front()->swapRight = temp21;
			temp21->parent = Q.front();
			Q.push(temp21);
			//swapLeft node and push onto queue
			if(checkpoint3 == false){
				node* temp22 = new node;
				temp22->puzzle = Q.front()->puzzle;
				swap(temp22->puzzle.at(emptyTileRow).at(emptyTileCol), temp22->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
				Q.front()->swapLeft = temp22;
				temp22->parent = Q.front();
				Q.push(temp22);
			}
			//push node onto end of queue after linking nodes to their parent's
		}
		if(emptyTileRow == 2 && emptyTileCol == 2){
			//swapLeft node and push onto queue
			node* temp23 = new node;
			temp23->puzzle = Q.front()->puzzle;
			swap(temp23->puzzle.at(emptyTileRow).at(emptyTileCol), temp23->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			Q.front()->swapLeft = temp23;
			temp23->parent = Q.front();
			Q.push(temp23);
			//swapTop node and push on to queue
			node* temp24 = new node;
			temp24->puzzle = Q.front()->puzzle;
			swap(temp24->puzzle.at(emptyTileRow).at(emptyTileCol), temp24->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			Q.front()->swapTop = temp24;
			temp24->parent = Q.front();
			Q.push(temp24);
			//push node onto end of queue after linking nodes to their parent's
		}
		if(popLater){
			Q.pop();
		}
	}
}

#endif