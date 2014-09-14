#pragma once
#include"Block.h"
#include"DataBlock.h"
#include"INodeBlock.h"
#include "INode.h"
class SuperBlock
{
private:
	DataBlock datablock;//									15MB
	INodeBlock inodeBlock;//								128KB
	
	int freeINodeStack[1024];//¿ÕÏÐinodeºÅ					4KB 
	int freeBlockStack[1024*15];//¿ÕÏÐµÄblockºÅ				60KB

	int freeINodeStackTop;//Õ»¶¥
	int freeBlockStackTop;//Õ»¶¥

	int inodeTotalNum;
	int blockTotalNum;

	int totalKB;
public:
	int TotalKB() { return totalKB; }
	int FreeINodeStackTop() const;
	void FreeINodeStackTop(int val);

	int BlockTotalNum() const;
	int InodeTotalNum() const;

	int FreeBlockStackTop() const;
	void FreeBlockStackTop(int val);

	int allocNewINode();
	void freeINode(int index);
	int allocNewBlock();
	void freeBlock(int index);

	void getINodeFromDisk(INode *inode,int index);
	void writeINodeToDisk(INode *inode,int index);

	void getBlockFromDisk(Block *block,int index);
	void writeBlockToDisk(Block *block,int index);


	SuperBlock(void);
	~SuperBlock(void);
};

