#include "SuperBlock.h"


SuperBlock::SuperBlock(void)
{
	totalKB=15*1024+128;
	inodeTotalNum=1024;
	blockTotalNum=15*1024;
	freeINodeStackTop=inodeTotalNum-1;
	freeBlockStackTop=blockTotalNum-1;
	for(int i=0;i<inodeTotalNum;i++)
		freeINodeStack[i]=inodeTotalNum-1-i;
	for(int i=0;i<blockTotalNum;i++)
		freeBlockStack[i]=blockTotalNum-1-i;
}


SuperBlock::~SuperBlock(void)
{

}

void SuperBlock::getINodeFromDisk( INode *inode,int index )
{
	int blockNum = index/8;
	int blockOffset=index%8;
	memcpy(inode,&(inodeBlock.block[blockNum].blockArray[blockOffset*128]),sizeof(*inode));
}

void SuperBlock::writeINodeToDisk( INode *inode,int index )
{
	int blockNum = index/8;
	int blockOffset=index%8;
	memcpy(&(inodeBlock.block[blockNum].blockArray[blockOffset*128]),inode,sizeof(*inode));
}

int SuperBlock::allocNewINode()
{
	if(freeINodeStackTop<=-1)return -1;//²»¹»freeINode
	else return freeINodeStack[freeINodeStackTop--];
}

void SuperBlock::freeINode( int index )
{
	if(freeINodeStackTop>=inodeTotalNum-1){
		printf("There is no free place!Must be something wrong");
		return;
	}else freeINodeStack[++freeINodeStackTop]=index;
}

int SuperBlock::allocNewBlock()
{
	if(freeBlockStackTop<=-1)return -1;//²»¹»freeINode
	else return freeBlockStack[freeBlockStackTop--];
}

void SuperBlock::freeBlock(int index)
{
	if(freeBlockStackTop>=blockTotalNum-1){
		printf("There is no free place for block!Must be something wrong");
		return;
	}else freeBlockStack[++freeBlockStackTop]=index;
}

void SuperBlock::getBlockFromDisk( Block *block,int index )
{
	memcpy(block,&datablock.data[index],sizeof(*block));
}

void SuperBlock::writeBlockToDisk( Block *block,int index )
{
	memcpy(&datablock.data[index],block,sizeof(*block));
}

int SuperBlock::FreeINodeStackTop() const
{
	return freeINodeStackTop;
}

void SuperBlock::FreeINodeStackTop( int val )
{
	freeINodeStackTop = val;
}

int SuperBlock::FreeBlockStackTop() const
{
	return freeBlockStackTop;
}

void SuperBlock::FreeBlockStackTop( int val )
{
	freeBlockStackTop = val;
}

int SuperBlock::InodeTotalNum() const
{
	return inodeTotalNum;
}

int SuperBlock::BlockTotalNum() const
{
	return blockTotalNum;
}


