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
/* �ڴ�������ࣺ
/* File: ��С��32�洢�����ļ���inode��Ϣ����Ӳ������洢����32���ַ���һ��block���Դ洢32��
/* MyDirectory����С��32�洢�����ļ���inode��Ϣ����Ӳ������洢����32���ַ���һ��block���Դ洢32��
/* ��ʼ��ʱ��root directory�洢��0�ڵ㣬��block 0   ֮��·������root·��
/* 
/* 
/* 
/* 
/* 
/* 
/*                                                                    
/************************************************************************/
