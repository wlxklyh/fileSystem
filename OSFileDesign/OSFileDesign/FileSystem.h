#pragma once
#include "head.h"
#include"INode.h"
#include "SuperBlock.h"
class FileSystem
{
private:
	char *COMMAND[20];
	int commandNum;
	std::fstream user;
	//login
	char userGroup[6];
	char userName[6];
	char passWord[6];

	SuperBlock superBlock;

	//���̸ı�Ķ���
	string direArray[100];
	char nowFileName[12];
	int roadStack[100];//��������100��
	int nowRoadStackTop;
public:
	//KO
	void welcome();
	//KO
	bool login();

	void changePassword();

	//KO
	void getCommand();

	//cmd
	void help();
	void createDir(char *filename);
	void deleteDir(char *filename);
	void dir();
	void changeDir(char *fileName);
	void find(char *filename);
	void createFile(char *filename,int fileSize);
	void deleteFile(char *filename);
	void cat(char *filename);
	void cp(char *desFilename,char *srcFilename);
	void chmod(char *filename,int mod);
	void chown(char *filename,char* toOwner);
	void chgrp(char *fileName,char* toGroup);
	void chnam(char *filename,char* toFileName);
	void sum();
	void logout();

	FileSystem(void);
	~FileSystem(void);
	//-1�����ҵ�
	int findFileInodeIndex(char* filename);
	void printFile(int inodeIndex);
	void printNowRoad(void);
	int findFileInodeFaIndex(char * filename);
};

