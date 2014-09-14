#include "MyDirectory.h"
#include "head.h"

MyDirectory::MyDirectory(void)
{
}


MyDirectory::~MyDirectory(void)
{
}

void MyDirectory::setName( char *val )
{
	memcpy(name,val,strlen(val)+1);
}

const char* MyDirectory::Name() const
{
	return name;
}

int MyDirectory::Index() const
{
	return index;
}

void MyDirectory::setIndex( int val )
{
	index = val;
}

const char*MyDirectory::FatherName() const
{
	return fatherName;
}

void MyDirectory::setFatherName( char *val )
{
	memcpy(fatherName,val,strlen(val)+1);
}

int MyDirectory::FaIndex() const
{
	return fatherIndex;
}

void MyDirectory::setFaIndex( int val )
{
	fatherIndex = val;
}
