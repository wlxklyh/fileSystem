#pragma once
/* @Date:		2014.2.9
 * @Authour：	Linyanhou
 * @function:	存储INode
 *  unix INode size is 64B
 */
#include "head.h"
class INode
{
private:
	//如果是directory只能是一个块  也就是1024/32=32个目录  取直接地址第一个
	//如果是文件的话可以是21+256块
	int fileSize;//文件大小			32bit可以表示4GB大小  单位Byte			0~3B	4B
	int blockNum;//文件占用的块的数量	4GB需要2^22但是用32位表示 浪费10bit		4~7B	4B
	//地址  一共15*1024块 算是2^14  5位是偏移量
	int directAdd[20];//直接地址		小于21个块的可以直接存在这里				8~91B	80B
	int indirectAdd;//???? 间接地址	大于21个块的可以直接存在这里				92~95B	4B
	char owner[10];//文件拥有者											96~105B	9B
	char group[10];//文件归属的组											106~114B	9B
	bool isDiretory;//是否是目录											114~114B	1B
	byte authourity[3];//Own Group Others								115~117B	3B
	char fileModifyTime[12];//文件修改时间	71~80B							117~127B	10B
public:
	int FileSize() const;
	void FileSize(int val);

	int BlockNum() const;
	void BlockNum(int val);

	int*DirectAdd();
	void DirectAdd(int pos,int val);

	int IndirectAdd();
	void IndirectAdd(int val);

	const char*Owner() const;
	void Owner(char *val);

	const char*Group() const;
	void Group(char *val);

	bool IsDiretory();
	void IsDiretory(bool val);



	const char* FileModifyTime() const;
	void FileModifyTime(char *val);

	INode(void);
	~INode(void);
private:

public:
	void getTime(int * year, int * month, int * day, int * hour, int * minutes);
};

