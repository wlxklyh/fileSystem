#include "INode.h"
#include <cstdio>
INode::INode(void)
{
	fileSize=0;
	blockNum=0;
	for(int i=0;i<20;i++)directAdd[i]=-1;
	indirectAdd=-1;
	memset(owner,0,sizeof(owner));
	memset(group,0,sizeof(group));
	isDiretory=false;
	memset(authourity,0,sizeof(authourity));
	memset(fileModifyTime,0,sizeof(fileModifyTime));
	
	SYSTEMTIME sys; 
	GetLocalTime( &sys );
	sys.wDay;
	char str[20];
	sprintf( str,
		"%4d%02d%02d%02d%02d",
		sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute); 
	for(int i=0;i<12;i++)
		fileModifyTime[i]=str[i];
	//fileModifyTime
}


INode::~INode(void)
{
}

int INode::FileSize() const
{
	return fileSize;
}

void INode::FileSize( int val )
{
	fileSize = val;
}

int INode::BlockNum() const
{
	return blockNum;
}

void INode::BlockNum( int val )
{
	blockNum = val;
}

int* INode::DirectAdd()
{
	return directAdd;
}

void INode::DirectAdd( int pos,int val )
{
	if(pos<5)directAdd[pos] = val;printf("out of array error!");
}

int INode::IndirectAdd()
{
	return indirectAdd;
}

void INode::IndirectAdd( int val )
{
	indirectAdd = val;
}

const char* INode::Owner() const
{
	return owner;
}

void INode::Owner( char *val )
{
	int len = strlen(val);for(int i=0;i<len;i++)owner[i]=val[i];
}

const char* INode::Group() const
{
	return group;
}

void INode::Group( char *val )
{
	int len=strlen(val);for(int i=0;i<len;i++)group[i] = val[i];
}

bool INode::IsDiretory()
{
	return isDiretory;
}

void INode::IsDiretory( bool val )
{
	isDiretory=val;
}

const char* INode::FileModifyTime() const
{
	return fileModifyTime;
}

void INode::FileModifyTime( char *val )
{
	int len=strlen(val); for(int i=0;i<len;i++)fileModifyTime[i] = val[i];
}



void INode::getTime(int * year, int * month, int * day, int * hour, int * minutes)
{
	sscanf(fileModifyTime,"%4d%2d%2d%2d%2d",year,month,day,hour,minutes);
}
