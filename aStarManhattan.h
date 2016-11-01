#ifndef ASTARMANHATTAN_H_INCLUDED
#define ASTARMANHATTAN_H_INCLUDED

#include <iostream>
#include <queue>
#include "treeNode.h"

using namespace std;

//aStarManhattan is same as UCS except it continues on the node with less steps to the goal
//  so have a counter: "int totalSlidesTilGoal" and instead of searching Q.front() every the time,
//  compare all the paths and search the path with the smallest total distance from root to goal

int calcManhattanDistance(node* x){
	int MD = 0;
	int goalRow;
	int goalCol;
	bool leaveEarly = false;
	int tempI;
	int tempJ;
	
    //goal 2D vector
	vector< vector<double> > goal2;
	goal2.resize(numCol, vector<double> (numRow, 0));
	goal2.at(0).at(0) = 1;
	goal2.at(0).at(1) = 2;
	goal2.at(0).at(2) = 3;

	goal2.at(1).at(0) = 4;
	goal2.at(1).at(1) = 5;
	goal2.at(1).at(2) = 6;

	goal2.at(2).at(0) = 7;
	goal2.at(2).at(1) = 8;
	goal2.at(2).at(2) = 0;
	
	node* goal = new node;
	goal->puzzle = goal2;
	
	//find misplaced tiles and calc MD for each of them
	for(int i = 0; i < numRow; i++){
		for(int j = 0; j < numCol; j++){
			if(x->puzzle.at(i).at(j) != goal->puzzle.at(i).at(j) && x->puzzle.at(i).at(j) != 0){
				// cout << "I: " << i << endl;
				// cout << "J: " << j << endl;
				//have position of misplaced tile, now calc MD for this tile
				//find k and l of where the tile is in goal node puzzle
				leaveEarly = false;
				for(int k = 0; k < numRow; k++){
					for(int l = 0; l < numCol; l++){
						if(x->puzzle.at(i).at(j) == goal->puzzle.at(k).at(l)){
							// cout << "Set GoalRow and GoalCol" << endl;
							goalRow = k;
							goalCol = l;
							leaveEarly = true;
							break;
						}
					}
					if(leaveEarly == true){
						break;
					}
				}
				// cout << "GoalRow: " << goalRow << endl;
				// cout << "GoalCol: " << goalCol << endl;
				tempI = i;
				tempJ = j;
				//add manhattan distance of specific tile found
				while(goalRow != tempI || goalCol != tempJ){
					if(tempI > goalRow){
						tempI--;
						MD++;
					}
					if(tempI < goalRow){
						tempI++;
						MD++;
					}
					if(tempJ > goalCol){
						tempJ--;
						MD++;
					}
					if(tempJ < goalCol){
						tempJ++;
						MD++;
					}
				}
				//continue with for loops to find next misplaced tile
			}
		}
	}
	return MD;
}

//custom priority determiner for priority queue of node*
struct customPriorityDeterminerMD{
    bool operator()(node* &lhs, node* &rhs){    //suppose to be: bool operator()(const node* &lhs, node* &rhs) const{
        //(findMisplacedTiles(lhs) + lhs->totalMoves) is the f(n) = g(n) + h(n)
        //sets the value with the lower ( < ) amount to a higher priority (hopefully)
        return ((calcManhattanDistance(lhs) + lhs->totalMoves) > (calcManhattanDistance(rhs) + rhs->totalMoves));
    }
};

//make children nodes of potential moves and push them onto priority queue
void PopParentMakeChildNodeAndPush(node* x, priority_queue<node*, vector<node*>, customPriorityDeterminerMD> &Q){
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

void aStarManhattan(node* &x, node* goal){
    priority_queue<node*, vector<node*>, customPriorityDeterminerMD> Q;
    Q.push(x);  //push root
    
    while(true){    //iterate forever (breaks out when solution is found)
        //check if top priority element is equal to goal
        if(Q.top()->puzzle == goal->puzzle){
            cout << "Solution found; return" << endl;
            x = Q.top();
            return;
        }
        
        //pop parent off and push it's children
        PopParentMakeChildNodeAndPush(Q.top(), Q);
    }
}

#endif