// =====HEADER=====
// CS 170 Individual Project 1
// Name: Thien Chau
// SID: 861145164
// Discussion Section: 021
// =====HEADER=====
#ifndef UCS_H_INCLUDED
#define UCS_H_INCLUDED

#include <iostream>
#include <queue>
#include "treeNode.h"

// //custom priority determiner for priority queue of node*
// struct customPriorityDeterminerUCS{
//     bool operator()(node* &lhs, node* &rhs){    //suppose to be: bool operator()(const node* &lhs, node* &rhs) const{
//         //(findMisplacedTiles(lhs) + lhs->totalMoves) is the f(n) = g(n) + h(n)
//         //sets the value with the lower ( < ) amount to a higher priority (hopefully)
//         return ((findMisplacedTiles(lhs) + lhs->totalMoves) > (findMisplacedTiles(rhs) + rhs->totalMoves));
//     }
// };

//make children nodes of potential moves and push them onto priority queue
void PopParentMakeChildNodeAndPush(node* x, queue<node*> &Q){
    //provide choices based on x and connect children to parent and parent to children
    //do "everything" here
    
    //pop node with highest priority off of the queue, and push it's children
    node* parent = x;   //store pointer to x in parent
    Q.pop();    //pop Q.top() which is x
    x = parent; //set x to parent
    
    //find where empty tile is
    int emptyTileCol;
    int emptyTileRow;
	for(int i = 0; i < numRow; i++){
		for(int j = 0; j < numCol; j++){
			if(x->puzzle.at(i).at(j) == 0){
				emptyTileRow = i;
				emptyTileCol = j;
			}
		}
	}
    
    //provides new nodes with potential moves based on emptyTileRow and emptyTileCol
    //now what do we do with the nodes?
    //we should push children node onto the priority queue.
	if(emptyTileRow == 0 && emptyTileCol == 0){
		//swapRight node and push onto queue
		if(x->swapMove != "swapLeft"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			x->swapRight = temp;
			temp->parent = x;
			temp->swapMove = "swapRight";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapBot node and push on to queue
		if(x->swapMove != "swapTop"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			x->swapBot = temp;
			temp->parent = x;
			temp->swapMove = "swapBot";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 0 && emptyTileCol == 1){
		//swapLeft node and push onto queue
		if(x->swapMove != "swapRight"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			x->swapLeft = temp;
			temp->parent = x;
			temp->swapMove = "swapLeft";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapRight node and push onto queue
		if(x->swapMove != "swapLeft"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			x->swapRight = temp;
			temp->parent = x;
			temp->swapMove = "swapRight";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapBot node and push on to queue
		if(x->swapMove != "swapTop"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			x->swapBot = temp;
			temp->parent = x;
			temp->swapMove = "swapBot";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 0 && emptyTileCol == 2){
		//swapLeft node and push onto queue
		if(x->swapMove != "swapRight"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			x->swapLeft = temp;
			temp->parent = x;
			temp->swapMove = "swapLeft";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapBot node and push on to queue
		if(x->swapMove != "swapTop"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			x->swapBot = temp;
			temp->parent = x;
			temp->swapMove = "swapBot";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 1 && emptyTileCol == 0){
		//swapTop node and push on to queue
		if(x->swapMove != "swapBot"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			x->swapTop = temp;
			temp->parent = x;
			temp->swapMove = "swapTop";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapBot node and push on to queue
		if(x->swapMove != "swapTop"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			x->swapBot = temp;
			temp->parent = x;
			temp->swapMove = "swapBot";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapRight node and push onto queue
		if(x->swapMove != "swapLeft"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			x->swapRight = temp;
			temp->parent = x;
			temp->swapMove = "swapRight";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 1 && emptyTileCol == 1){
		//swapTop node and push on to queue
		if(x->swapMove != "swapBot"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			x->swapTop = temp;
			temp->parent = x;
			temp->swapMove = "swapTop";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapBot node and push on to queue
		if(x->swapMove != "swapTop"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			x->swapBot = temp;
			temp->parent = x;
			temp->swapMove = "swapBot";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapRight node and push onto queue
		if(x->swapMove != "swapLeft"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			x->swapRight = temp;
			temp->parent = x;
			temp->swapMove = "swapRight";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapLeft node and push onto queue
		if(x->swapMove != "swapRight"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			x->swapLeft = temp;
			temp->parent = x;
			temp->swapMove = "swapLeft";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 1 && emptyTileCol == 2){
    	//swapTop node and push on to queue
		if(x->swapMove != "swapBot"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			x->swapTop = temp;
			temp->parent = x;
			temp->swapMove = "swapTop";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapBot node and push on to queue
		if(x->swapMove != "swapTop"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			x->swapBot = temp;
			temp->parent = x;
			temp->swapMove = "swapBot";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapLeft node and push onto queue
		if(x->swapMove != "swapRight"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			x->swapLeft = temp;
			temp->parent = x;
			temp->swapMove = "swapLeft";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 2 && emptyTileCol == 0){
		//swapTop node and push on to queue
		if(x->swapMove != "swapBot"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			x->swapTop = temp;
			temp->parent = x;
			temp->swapMove = "swapTop";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapRight node and push onto queue
		if(x->swapMove != "swapLeft"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			x->swapRight = temp;
			temp->parent = x;
			temp->swapMove = "swapRight";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 2 && emptyTileCol == 1){
		//swapTop node and push on to queue
		if(x->swapMove != "swapBot"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			x->swapTop = temp;
			temp->parent = x;
			temp->swapMove = "swapTop";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapRight node and push onto queue
		if(x->swapMove != "swapLeft"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			x->swapRight = temp;
			temp->parent = x;
			temp->swapMove = "swapRight";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapLeft node and push onto queue
		if(x->swapMove != "swapRight"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			x->swapLeft = temp;
			temp->parent = x;
			temp->swapMove = "swapLeft";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
	if(emptyTileRow == 2 && emptyTileCol == 2){
		//swapLeft node and push onto queue
		if(x->swapMove != "swapRight"){
	    	node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			x->swapLeft = temp;
			temp->parent = x;
			temp->swapMove = "swapLeft";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
		//swapTop node and push on to queue
		if(x->swapMove != "swapBot"){
			node* temp = new node;
			temp->puzzle = x->puzzle;
			swap(temp->puzzle.at(emptyTileRow).at(emptyTileCol), temp->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			x->swapTop = temp;
			temp->parent = x;
			temp->swapMove = "swapTop";
			temp->totalMoves = (temp->parent->totalMoves) + 1;
			Q.push(temp);
		}
	}
}

void uniformCostSearch(node* &x, node* goal){
    queue<node*> Q;
    Q.push(x);  //push root
    
    while(true){    //iterate forever (breaks out when solution is found)
        //check if top priority element is equal to goal
        if(Q.front()->puzzle == goal->puzzle){
            cout << "Solution found; return" << endl;
            x = Q.front();
            return;
        }
        
        //pop parent off and push it's children
        PopParentMakeChildNodeAndPush(Q.front(), Q);
    }
}

#endif