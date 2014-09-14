#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <string>
using namespace std;


const static int SETTING_FILE_MAX_SIZE=282624;
const static int FILE_NAME_LENGHT=12;

/*
 *  Requirement:
 *	block:1KB  
 *	block address:32bit  4Byte
 *  HardDisk Size:
 *	INode:1024			64KB  
 *  Datablock:15*1024	15MB
 *  SuperBlock:         512KB
 *  Leadblock:          448KB
 *  fileMaxSize:        (256+20)*1024
 */


/************************************************************************/
/* 内存里面的类：
/* File: 大小是32存储的是文件的inode信息、在硬盘里面存储则是32个字符，一个block可以存储32个
/* MyDirectory：大小是32存储的是文件的inode信息、在硬盘里面存储则是32个字符，一个block可以存储32个
/* 开始的时候，root directory存储在0节点，在block 0   之后路径进入root路径
/* 
/* 
/* 
/* 
/* 
/* 
/*                                                                    
/************************************************************************/
