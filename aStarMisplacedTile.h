#ifndef ASTARMISPLACEDTILE_H_INCLUDED
#define ASTARMISPLACEDTILE_H_INCLUDED

#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include "treeNode.h"

using namespace std;

//aStarMisplacedTile is same as UCS except it continues on the node with less steps to the goal
//  so have a counter: "int totalMisplacedTiles" and instead of searching Q.front() every the time before moving on,
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

//UCS search on root node x
//GETS KILLED ON COMPLEX 8 PUZZLES
void aStarMisplacedTile(node* &x, node* goal){
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
	
	//traverse "tree" by creating nodes that are potential moves
	//if potential state == goal state, exit
	int emptyTileRow = 0;
	int emptyTileCol = 0;
	bool checkpoint = false;    //checkpoints to prevent duplicate puzzles
	bool checkpoint2 = false;
	bool checkpoint3 = false;
	bool didSet = false;		//used to check if lowest child is set to current node at end
	map<string, int> choices;   //map used to choose node with less misplaced tiles
    int totalMisplacedTiles = 0;
    int firstIteration = 0;
	while(true){
	    if(firstIteration == 0){
	        currentNode = x;
	        firstIteration = 1;
	    }
	    
		//if top row is 1 2 3, do not switch puzzle.at(0).at(0), puzzle.at(0).at(1), and puzzle.at(0).at(2)
		if(currentNode->puzzle.at(0).at(0) == 1 && currentNode->puzzle.at(0).at(1) == 2 && currentNode->puzzle.at(0).at(2) == 3 && checkpoint2 == false){
			checkpoint = true;
		}
		if(currentNode->puzzle.at(0).at(0) == 1 && currentNode->puzzle.at(0).at(1) == 2 && currentNode->puzzle.at(0).at(2) == 3 
			&& currentNode->puzzle.at(1).at(0) == 4 && checkpoint3 == false){
			checkpoint2 = true;
		}
		if(currentNode->puzzle.at(0).at(0) == 1 && currentNode->puzzle.at(0).at(1) == 2 && currentNode->puzzle.at(0).at(2) == 3 
			&& currentNode->puzzle.at(1).at(0) == 4 && currentNode->puzzle.at(2).at(0) == 7){
			checkpoint3 = true;
		}
	    
	    //check for solution
		if(currentNode->puzzle == goal->puzzle){
			cout << "PUZZLE FOUND; exit" << endl;
			x = currentNode;	//set original node to solution node
			return;
		}
	    
		//find lowest node's empty tile, store row/column value
		//create nodes of swappable states. use swap()
		for(int i = 0; i < numRow; i++){
			for(int j = 0; j < numCol; j++){
				if(currentNode->puzzle.at(i).at(j) == 0){
					emptyTileRow = i;
					emptyTileCol = j;
				}
			}
		}
		
		//don't create duplicate puzzles
		//don't know how to handle --^ so just have duplicate puzzles
        //  tried to store all puzzles in a vector and compare every possible move puzzle with
        //  all puzzles in vector, if duplicate don't create puzzle; ran out of memory, storage vector too big
		if(emptyTileRow == 0 && emptyTileCol == 0){
			//swapRight node and push onto queue
			node* temp1 = new node;
			temp1->puzzle = currentNode->puzzle;
			swap(temp1->puzzle.at(emptyTileRow).at(emptyTileCol), temp1->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			currentNode->swapRight = temp1;
			temp1->parent = currentNode;
			
			//swapBot node and push on to queue
			node* temp2 = new node;
			temp2->puzzle = currentNode->puzzle;
			swap(temp2->puzzle.at(emptyTileRow).at(emptyTileCol), temp2->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			currentNode->swapBot = temp2;
			temp2->parent = currentNode;
		}
		if(emptyTileRow == 0 && emptyTileCol == 1){
			//swapLeft node and push onto queue
			node* temp3 = new node;
			temp3->puzzle = currentNode->puzzle;
			swap(temp3->puzzle.at(emptyTileRow).at(emptyTileCol), temp3->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			currentNode->swapLeft = temp3;
			temp3->parent = currentNode;
			
			//swapRight node and push onto queue
			node* temp4 = new node;
			temp4->puzzle = currentNode->puzzle;
			swap(temp4->puzzle.at(emptyTileRow).at(emptyTileCol), temp4->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			currentNode->swapRight = temp4;
			temp4->parent = currentNode;
			
			//swapBot node and push on to queue
			node* temp5 = new node;
			temp5->puzzle = currentNode->puzzle;
			swap(temp5->puzzle.at(emptyTileRow).at(emptyTileCol), temp5->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			currentNode->swapBot = temp5;
			temp5->parent = currentNode;
		}
		if(emptyTileRow == 0 && emptyTileCol == 2){
			//swapLeft node and push onto queue
			node* temp6 = new node;
			temp6->puzzle = currentNode->puzzle;
			swap(temp6->puzzle.at(emptyTileRow).at(emptyTileCol), temp6->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			currentNode->swapLeft = temp6;
			temp6->parent = currentNode;
			
			//swapBot node and push on to queue
			node* temp7 = new node;
			temp7->puzzle = currentNode->puzzle;
			swap(temp7->puzzle.at(emptyTileRow).at(emptyTileCol), temp7->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			currentNode->swapBot = temp7;
			temp7->parent = currentNode;
		}
		if(emptyTileRow == 1 && emptyTileCol == 0){
			//swapTop node and push on to queue
			if(checkpoint == false){
    			node* temp8 = new node;
    			temp8->puzzle = currentNode->puzzle;
        		swap(temp8->puzzle.at(emptyTileRow).at(emptyTileCol), temp8->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
    			currentNode->swapTop = temp8;
    			temp8->parent = currentNode;
			}
			
			//swapBot node and push on to queue
			node* temp9 = new node;
			temp9->puzzle = currentNode->puzzle;
			swap(temp9->puzzle.at(emptyTileRow).at(emptyTileCol), temp9->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			currentNode->swapBot = temp9;
			temp9->parent = currentNode;
			
			//swapRight node and push onto queue
			node* temp10 = new node;
			temp10->puzzle = currentNode->puzzle;
			swap(temp10->puzzle.at(emptyTileRow).at(emptyTileCol), temp10->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			currentNode->swapRight = temp10;
			temp10->parent = currentNode;
		}
		if(emptyTileRow == 1 && emptyTileCol == 1){
			//swapTop node and push on to queue
			if(checkpoint == false){
    			node* temp11 = new node;
    			temp11->puzzle = currentNode->puzzle;
    			swap(temp11->puzzle.at(emptyTileRow).at(emptyTileCol), temp11->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
    			currentNode->swapTop = temp11;
        		temp11->parent = currentNode;
			}
			
			//swapBot node and push on to queue
			node* temp12 = new node;
			temp12->puzzle = currentNode->puzzle;
			swap(temp12->puzzle.at(emptyTileRow).at(emptyTileCol), temp12->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			currentNode->swapBot = temp12;
			temp12->parent = currentNode;
			
			//swapRight node and push onto queue
			node* temp13 = new node;
			temp13->puzzle = currentNode->puzzle;
			swap(temp13->puzzle.at(emptyTileRow).at(emptyTileCol), temp13->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			currentNode->swapRight = temp13;
			temp13->parent = currentNode;
			
			//swapLeft node and push onto queue
			if(checkpoint2 == false){
    			node* temp14 = new node;
    			temp14->puzzle = currentNode->puzzle;
    			swap(temp14->puzzle.at(emptyTileRow).at(emptyTileCol), temp14->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
    			currentNode->swapLeft = temp14;
    			temp14->parent = currentNode;
			}
		}
		if(emptyTileRow == 1 && emptyTileCol == 2){
			//swapTop node and push on to queue
			if(checkpoint == false){
    			node* temp15 = new node;
    			temp15->puzzle = currentNode->puzzle;
    			swap(temp15->puzzle.at(emptyTileRow).at(emptyTileCol), temp15->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
    			currentNode->swapTop = temp15;
    			temp15->parent = currentNode;
			}
			
			//swapBot node and push on to queue
			node* temp16 = new node;
			temp16->puzzle = currentNode->puzzle;
			swap(temp16->puzzle.at(emptyTileRow).at(emptyTileCol), temp16->puzzle.at(emptyTileRow + 1).at(emptyTileCol));
			currentNode->swapBot = temp16;
			temp16->parent = currentNode;
			
			//swapLeft node and push onto queue
			node* temp17 = new node;
			temp17->puzzle = currentNode->puzzle;
			swap(temp17->puzzle.at(emptyTileRow).at(emptyTileCol), temp17->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			currentNode->swapLeft = temp17;
			temp17->parent = currentNode;
		}
		if(emptyTileRow == 2 && emptyTileCol == 0){
			//swapTop node and push on to queue
			if(checkpoint2 == false){
    			node* temp18 = new node;
    			temp18->puzzle = currentNode->puzzle;
    			swap(temp18->puzzle.at(emptyTileRow).at(emptyTileCol), temp18->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
    			currentNode->swapTop = temp18;
    			temp18->parent = currentNode;
			}
			
			//swapRight node and push onto queue
			node* temp19 = new node;
			temp19->puzzle = currentNode->puzzle;
			swap(temp19->puzzle.at(emptyTileRow).at(emptyTileCol), temp19->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			currentNode->swapRight = temp19;
			temp19->parent = currentNode;
		}
		if(emptyTileRow == 2 && emptyTileCol == 1){
			//swapTop node and push on to queue
			node* temp20 = new node;
			temp20->puzzle = currentNode->puzzle;
			swap(temp20->puzzle.at(emptyTileRow).at(emptyTileCol), temp20->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			currentNode->swapTop = temp20;
			temp20->parent = currentNode;
			
			//swapRight node and push onto queue
			node* temp21 = new node;
			temp21->puzzle = currentNode->puzzle;
			swap(temp21->puzzle.at(emptyTileRow).at(emptyTileCol), temp21->puzzle.at(emptyTileRow).at(emptyTileCol + 1));
			currentNode->swapRight = temp21;
			temp21->parent = currentNode;
			
			//swapLeft node and push onto queue
			if(checkpoint3 == false){
    			node* temp22 = new node;
    			temp22->puzzle = currentNode->puzzle;
    			swap(temp22->puzzle.at(emptyTileRow).at(emptyTileCol), temp22->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
    			currentNode->swapLeft = temp22;
    			temp22->parent = currentNode;
			}
		}
		if(emptyTileRow == 2 && emptyTileCol == 2){
			//swapLeft node and push onto queue
			node* temp23 = new node;
			temp23->puzzle = currentNode->puzzle;
			swap(temp23->puzzle.at(emptyTileRow).at(emptyTileCol), temp23->puzzle.at(emptyTileRow).at(emptyTileCol - 1));
			currentNode->swapLeft = temp23;
			temp23->parent = currentNode;
			
			//swapTop node and push on to queue
			node* temp24 = new node;
			temp24->puzzle = currentNode->puzzle;
			swap(temp24->puzzle.at(emptyTileRow).at(emptyTileCol), temp24->puzzle.at(emptyTileRow - 1).at(emptyTileCol));
			currentNode->swapTop = temp24;
			temp24->parent = currentNode;
		}
		
		//set currentNode to it's child that has less misplaced tiles
		didSet = false;
		while(didSet == false){
		    if(currentNode->swapTop != 0){
		        choices["Swap Top"] = findMisplacedTiles(currentNode->swapTop, goal);
		    }
		    if(currentNode->swapBot != 0){
		        choices["Swap Bot"] = findMisplacedTiles(currentNode->swapBot, goal);
		    }
		    if(currentNode->swapRight != 0){
		        choices["Swap Right"] = findMisplacedTiles(currentNode->swapRight, goal);
		    }
		    if(currentNode->swapLeft != 0){
		        choices["Swap Left"] = findMisplacedTiles(currentNode->swapLeft, goal);
		    }
		    typedef map<string, int>::iterator it_type;
		    int lowest = findMisplacedTiles(currentNode, goal);
		    string lowestNodeString = "";
		    for(it_type iterator = choices.begin(); iterator != choices.end(); iterator++){
		        if(iterator->second < lowest){
		            lowestNodeString = iterator->first;
		            lowest = iterator->second;
		        }
		    }
		    if(lowestNodeString == "Swap Top"){
		        currentNode = currentNode->swapTop;
		    }
		    if(lowestNodeString == "Swap Bot"){
		        currentNode = currentNode->swapBot;
		    }
		    if(lowestNodeString == "Swap Right"){
		        currentNode = currentNode->swapRight;
		    }
		    if(lowestNodeString == "Swap Left"){
		        currentNode = currentNode->swapLeft;
		    }
		    //how to know if currentNode's children all have the same # of
		    //misplaced tiles?
		    //need to go back to root node and go down other branch
		    //  in order to do this, need a flag to see where you at the root node
		    //  make flags: wentTop, wentBot, wentLeft, wentRight 
		    //  if you fall into this situation, go back to root node and go down path
		    //  you haven't gone down yet
		    didSet = true;
		}
	}
}

#endif