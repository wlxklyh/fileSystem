#pragma once
class MyDirectory
{
private:
	char name[12];              //12B
	int index;					//4B
	char fatherName[12];        //12B
	int fatherIndex;				//4B
public:
	MyDirectory(void);
	~MyDirectory(void);

	const char *Name() const;
	void setName(char *val);

	int Index() const;
	void setIndex(int val);

	const char *FatherName() const;
	void setFatherName(char *val);

	int FaIndex() const;
	void setFaIndex(int val);
};

