CC = g++
CFLAGS = -w

all: compile

compile: hw1.cpp treeNode.h UCS.h aStarMisplacedTile.h aStarManhattan.h
	$(CC) $(CFLAGS) hw1.cpp treeNode.h UCS.h aStarMisplacedTile.h aStarManhattan.h
	
clean: rm -rf bin