#pragma once
/* @Date:		2014.2.9
 * @Authour��	Linyanhou
 * @function:	�洢INode
 *  unix INode size is 64B
 */
#include "head.h"
class INode
{
private:
	//�����directoryֻ����һ����  Ҳ����1024/32=32��Ŀ¼  ȡֱ�ӵ�ַ��һ��
	//������ļ��Ļ�������21+256��
	int fileSize;//�ļ���С			32bit���Ա�ʾ4GB��С  ��λByte			0~3B	4B
	int blockNum;//�ļ�ռ�õĿ������	4GB��Ҫ2^22������32λ��ʾ �˷�10bit		4~7B	4B
	//��ַ  һ��15*1024�� ����2^14  5λ��ƫ����
	int directAdd[20];//ֱ�ӵ�ַ		С��21����Ŀ���ֱ�Ӵ�������				8~91B	80B
	int indirectAdd;//???? ��ӵ�ַ	����21����Ŀ���ֱ�Ӵ�������				92~95B	4B
	char owner[10];//�ļ�ӵ����											96~105B	9B
	char group[10];//�ļ���������											106~114B	9B
	bool isDiretory;//�Ƿ���Ŀ¼											114~114B	1B
	byte authourity[3];//Own Group Others								115~117B	3B
	char fileModifyTime[12];//�ļ��޸�ʱ��	71~80B							117~127B	10B
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

