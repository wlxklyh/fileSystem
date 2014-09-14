#pragma once
#include <string>
#include <Windows.h>
class File
{
private:
	char name[12];
	int index;
	char fatherName[12];
	int fatherIndex;
public:
	char* getName();
	void setName(char* val);
};