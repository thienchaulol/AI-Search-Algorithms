CC = g++
CFLAGS = -w

all: compile

compile: hw1.cpp UCS.h treeNode.h
	$(CC) $(CFLAGS) hw1.cpp treeNode.h aStarMisplacedTile.h
	
clean: rm -rf bin