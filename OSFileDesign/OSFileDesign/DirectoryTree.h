#pragma once
#include "head.h"
struct dirTreeNode{
	int INodeIndex;
	char name[12];
	int size;// how manny Byte
	char group[6];
	dirTreeNode*leftSon;
	dirTreeNode*rightBrother;
	dirTreeNode(){
		size=-1;
		leftSon=NULL;
		rightBrother=NULL;
	};
};
class DirectoryTree
{
public:
	dirTreeNode *now;
public:
	DirectoryTree(void);
	~DirectoryTree(void);
};

