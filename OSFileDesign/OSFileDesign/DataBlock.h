#pragma once
#include "Block.h"
class DataBlock
{
public:
	const static int numOfNlock=15360;//15*1024
	Block data[15360];
public:
	DataBlock(void);
	~DataBlock(void);
};

