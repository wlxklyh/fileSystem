#include "FileSystem.h"
#include "MyDirectory.h"
#include "INode.h"
FileSystem::FileSystem(void)
{
	/*debug*/
	char userGroup2[6]="Lin";
	char userName2[6]="lyh";
	char passWord2[6]="123";
	memcpy(userGroup,userGroup2,6);
	memcpy(userName,userName2,6);
	memcpy(passWord,passWord2,6);

	nowRoadStackTop=0;
	int inodeindex = roadStack[0]=superBlock.allocNewINode();
	INode inodeRoot;
	inodeRoot.BlockNum(1);
	int blockindex = inodeRoot.DirectAdd()[0]=superBlock.allocNewBlock();
	inodeRoot.FileSize(0);
	inodeRoot.Group("");
	inodeRoot.IsDiretory(true);
	inodeRoot.Owner("");
	superBlock.writeINodeToDisk(&inodeRoot,inodeindex);

	INode tempINode;
	superBlock.getINodeFromDisk(&tempINode,inodeindex);

	char tempName[12]="root";
	memcpy(nowFileName,tempName,strlen(tempName)+1);
	direArray[0]="root";


	COMMAND[0] = "help";
	COMMAND[1] = "createDir";
	COMMAND[2] = "deleteDir";
	COMMAND[3] = "dir";
	COMMAND[4] = "changeDir";
	COMMAND[5] = "find";
	COMMAND[6] = "createFile";
	COMMAND[7] = "deleteFile";
	COMMAND[8] = "cat";
	COMMAND[9] = "cp";
	COMMAND[10]= "chmod";
	COMMAND[11]= "chown";
	COMMAND[12]= "chgrp";
	COMMAND[13]= "chnam";
	COMMAND[14]= "cls";
	COMMAND[15]= "sum";
	COMMAND[16]= "logout";
	commandNum=17;



	//mkdir("dir1");
	//mk("file1");
	//cd("dir1");
	//mkdir("dir2");
	//mk("file2");
	changeDir("/");
}				


FileSystem::~FileSystem(void)
{

}

bool FileSystem::login()
{
	while(1){
		bool isExit=false;
		bool isT=false;
		char userNameInput[6];
		char userPswInput[6];
		char userNameTXT[6];
		char userPswTXT[6];
		printf("==your name: ");
		scanf("%s",userNameInput);
		printf("==your password: ");
		scanf("%s",userPswInput);
		user.open("user.txt",ios::in);
		int usernum;
		user>>usernum;
		for(int n=0;n<usernum;n++)
		{
			user.seekg(18*n+6);
			user>>userNameTXT>>userPswTXT;
			int a=strcmp(userNameInput,userNameTXT);
			int b=strcmp(userPswInput,userPswTXT);
			if((!a)&&(!b))
			{
				user>>userGroup;
				user.close();
				isT = true;
				break;
			}
		}
		user.close();
		if(isT){ 
			printf("Login succeed!\n");
			return true;
		}
		else
		{
			char str[20];
			printf("The password is wrong or the account is wrong!Please input enter to try again or input exit to exit.\n");
			while(1){
				scanf("%s",str);
				if(!strcmp(str,"exit"))
					return false;
				else if(!strcmp(str,"enter"))
					break;
				else printf("The input is wrong!Please input enter to try again or input exit to exit.\n");
			}
		}
	}
}

void FileSystem::logout()
{
	return ;
}



void FileSystem::welcome()
{
	system("title                    欢迎界面 ");
	cout<<'\n'<<'\n';
	Sleep(100);
	char *welc = 
		"     →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→\n"
		"     → ***           **        **       ***      ***    ↓\n"
		"     → ***            **      **        ***      ***    ↓\n"
		"     → ***             **    **         ***      ***    ↓\n"
		"     → ***              **  **          ***      ***    ↓\n"
		"     → ***               ****           ************    ↓\n"
		"     → ***                **            ***      ***    ↓\n"
		"     → ***                **            ***      ***    ↓\n"
		"     → *********          **            ***      ***    ↓\n"
		"     → *********          **            ***      ***    ↓\n"
		"     →                       欢迎使用文件管理系统!                       ↓\n"
		"     →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→\n"
		"     →      →      →     →      →系统初始化中";
	for(int n=0; n<strlen(welc); n++) 
	{ 
		if(welc[n]!=' ') 
		{ 
			Sleep(5); 
		} 
		cout<<welc[n]; 
	} 
	for(int a =0; a<4; a++)
	{
		Sleep(500);
		cout<<'.';
	}
	Sleep(2000);
	system("cls");
}



//************************************
// help
// createDir dir1
// deleteDir dir1
// dir
// changeDir dir1
// find /dir1/file2
// createFile file1 100
// deleteFile file1
// cat /dir1/file2
// cp /dir1/file2 /dir1
// chmod /dir1/file2 7
// chown /dir1/file2 lyh
// chgrp /dir1/file2 guess
// chnam /dir1/file2 file3
// cls
// sum
// logout
//************************************
void FileSystem::getCommand()
{
	char command[20];
	string commandLine;
	bool isLogin=true;
	while(isLogin)
	{
		getline(cin,commandLine);
		int commandLineIndex=0;
		for(commandLineIndex=0;commandLineIndex<commandLine.length();commandLineIndex++){
			if(commandLine[commandLineIndex]==' '){command[commandLineIndex]='\0';commandLineIndex++;break;}
			command[commandLineIndex]=commandLine[commandLineIndex];
		}
		if (commandLineIndex==commandLine.length())
			command[commandLineIndex]='\0';

		bool isBreak;
		char filName0[200]="";int fileName0Index=0;
		char filName1[200]="";int fileName1Index=0;
		int fileSize=0;
		int i;
		for(i=0;i<commandNum;i++)
		{
			if(!strcmp(command,COMMAND[i]))
			{
				switch(i)
				{
				case 0:
					help();
					break;
				case 1:
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';

					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else createDir(filName0);
					break;
				case 2: 
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else
						deleteDir(filName0);
					break;			 
				case 3:				 
					dir();			
					break;			 
				case 4:	
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else
						changeDir(filName0);
					break;			 
				case 5:	
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else
						find(filName0);	
					break;
				case 6:	
					isBreak=false;
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						fileSize*=10;
						if(commandLine[commandLineIndex]<'0'|commandLine[commandLineIndex]>'9'){
							printf("Size must be number integer!\n");
							isBreak=true;
							break;
						}else {
							fileSize+=(commandLine[commandLineIndex]-'0');
						}
					}
					if(isBreak)break;
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else
						createFile(filName0,fileSize);			
					break;			 
				case 7:	
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else
						deleteFile(filName0);
					break;			 
				case 8:
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else
						cat(filName0);
					break;			 
				case 9:		
					for(;commandLineIndex<commandLine.length();commandLineIndex++){
						if(commandLine[commandLineIndex]==' '){commandLineIndex++;break;}
						filName0[fileName0Index++]=commandLine[commandLineIndex];
					}
					filName0[fileName0Index]='\0';
					if (!strcmp(filName0,""))
					{
						printf("file name is empty!\n");
					}else if(strlen(filName0)>FILE_NAME_LENGHT){
						printf("file name too long!\n");
					}
					else cp(filName0,filName1);///////remenber!!!
					break;			 
				case 10:
					scanf("%s",filName0);
					int mode;
					scanf("%d",mode);
					chmod(filName0,mode);
					break;
				case 11:
					scanf("%s",filName0);
					scanf("%s",filName1);
					chown(filName0,filName1);
					break;
				case 12:
					printf("Not Yet!");
					//scanf("%s",filName);
					//chgrp(filName);
					break;
				case 13:
					scanf("%s",filName0);
					scanf("%s",filName1);
					chnam(filName0,filName1);
					break;
				case 14:
					system("cls");
					break;
				case 15:
					sum();
					break;
				case 16:
					logout();
					isLogin=false;
					break;
				}
				break;
			}
		}
		if(i==commandNum)
		{
			printf("There is not exit this command!\n");
		}
	}
}


void FileSystem::help()
{
	char *help = "                           ★输入命令对照表★\n"
		"                         ☆输入  help 即可查询☆\n"
		"      →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→\n"
		"                                                                        \n"
		"         ★  help                                  操作帮助             \n"
		"         ★  createFile <filename>                 创建文件             \n"
		"         ★  deleteFile <filename>                 删除文件             \n"
		"         ★  createDir <foldername>                创建目录             \n"
		"         ★  deleteDir <foldername>                删除目录             \n"
		"         ★  dir                                   列出文件目录         \n"
		"         ★  cat <filename>                        读文件               \n"
		"         ★  cp <filenameA> <filenameB>            复制文件             \n"
		"         ★  logout                                用户退出             \n"
		"                                                                        \n"
		"      →→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→\n";
	for(int n=0; n<strlen(help); n++) 
	{ 
		if(help[n]!=' ') 
		{ 
			Sleep(1); 
		} 
		cout<<help[n]; 
	} 

	cout<<"                                                  按任意键返回!"<<endl;
	getchar();
	getchar();
	system("cls");
}

void FileSystem::createDir(char *filename)
{
	int InodeIndexTemp=findFileInodeIndex(filename);
	if(InodeIndexTemp!=-1){
		INode inode0;
		superBlock.getINodeFromDisk(&inode0,InodeIndexTemp);
		if(inode0.IsDiretory()){
			printf("The directory already is exitting!\n");
			return ;
		}
	}
	int nowINodeIndex = roadStack[nowRoadStackTop];
	if(filename[0]=='/')
	{
		nowINodeIndex = findFileInodeIndex(filename);
	}
	INode inodeTemp;
	superBlock.getINodeFromDisk(&inodeTemp,nowINodeIndex);
	if(!inodeTemp.IsDiretory()){printf("Can not make dir in file!");return;}

	if(inodeTemp.FileSize()>=1024){printf("There is no place for new directory!");return;}

	MyDirectory newDir;
	newDir.setName(filename);
	int newINodeIndex=superBlock.allocNewINode();


	INode inodeTemp2;
	inodeTemp2.BlockNum(1);
	int blockindex = inodeTemp2.DirectAdd()[0]=superBlock.allocNewBlock();
	inodeTemp2.FileSize(0);
	inodeTemp2.Group(userGroup);
	inodeTemp2.IndirectAdd(0);
	inodeTemp2.IsDiretory(true);
	inodeTemp2.Owner(userName);
	superBlock.writeINodeToDisk(&inodeTemp2,newINodeIndex);

	newDir.setIndex(newINodeIndex);
	newDir.setFatherName(nowFileName);
	newDir.setFaIndex(nowINodeIndex);

	Block blockTemp;
	superBlock.getBlockFromDisk(&blockTemp,inodeTemp.DirectAdd()[0]);
	memcpy(blockTemp.blockArray+inodeTemp.FileSize(),&newDir,sizeof(newDir));
	superBlock.writeBlockToDisk(&blockTemp,inodeTemp.DirectAdd()[0]);

	inodeTemp.FileSize(inodeTemp.FileSize()+32);
	superBlock.writeINodeToDisk(&inodeTemp,nowINodeIndex);
}

void FileSystem::deleteDir(char *fileName)
{
	//获取现在的INode节点
	int nowINodeIndex = roadStack[nowRoadStackTop];
	if(fileName[0]=='/')
	{
		nowINodeIndex=findFileInodeIndex(fileName);
	}
	INode inodeTemp;
	superBlock.getINodeFromDisk(&inodeTemp,nowINodeIndex);

	//获取现在的INode节点指向的块
	Block blockTemp;
	superBlock.getBlockFromDisk(&blockTemp,inodeTemp.DirectAdd()[0]);

	int fileSize=inodeTemp.FileSize();
	MyDirectory dir;
	int i;
	for(i=0;i<fileSize;i+=32)
	{
		memcpy(&dir,blockTemp.blockArray+i,sizeof(dir));
		INode inodeTemp2;
		superBlock.getINodeFromDisk(&inodeTemp2,dir.Index());
		if(inodeTemp2.IsDiretory()){
			if(!strcmp(fileName,dir.Name()))
			{
				superBlock.freeBlock(inodeTemp2.DirectAdd()[0]);
				superBlock.freeINode(dir.Index());
				for(int j=i;j<fileSize-32;j++)
				{
					blockTemp.blockArray[j]=blockTemp.blockArray[j+32];
				}
				superBlock.writeBlockToDisk(&blockTemp,inodeTemp.DirectAdd()[0]);
				inodeTemp.FileSize(inodeTemp.FileSize()-32);
				superBlock.writeINodeToDisk(&inodeTemp,nowINodeIndex);
				break;
			}
		}
	}
	if(i>fileSize)
	{
		printf("Directory not find!\n");
	}else{
		printf("%s already be delete!\n",fileName);
	}
}

void FileSystem::dir()
{
	int nowINodeIndex = roadStack[nowRoadStackTop];
	INode inodeTemp;
	superBlock.getINodeFromDisk(&inodeTemp,nowINodeIndex);

	Block blockTemp;
	superBlock.getBlockFromDisk(&blockTemp,inodeTemp.DirectAdd()[0]);

	int fileSize=inodeTemp.FileSize();
	MyDirectory dir;
	for(int i=0;i<fileSize;i+=32)
	{
		memcpy(&dir,blockTemp.blockArray+i,sizeof(dir));

		INode inodeTemp2;
		superBlock.getINodeFromDisk(&inodeTemp2,dir.Index());
		if(inodeTemp2.IsDiretory()){
			printf("%-12s[dir]  ",dir.Name());
		}else
		{
			printf("%-12s[file] ",dir.Name());
		}
		int year,month,dar,hour,minutes;
		inodeTemp2.getTime(&year,&month,&dar,&hour,&minutes);
		printf("%-6d%-10s%4d/%02d/%02d %02d:%02d\n",
			inodeTemp2.FileSize(),inodeTemp2.IsDiretory()?"Directory":"File",
			year,month,dar,hour,minutes);
	}
	printf("\n");
}

void FileSystem::changeDir(char *fileName)
{
	//(1)cd /home   cd+一个目录路径
	//(2)cd ..            跳转上一层目录
	//(3)cd -              返回到上一次的目录路径
	//(4)cd /              返回到根目录
	if(!strcmp(fileName,"/"))
	{
		char str[12]="root";
		memcpy(nowFileName,str,strlen(str)+1);
		nowRoadStackTop=0;
		roadStack[nowRoadStackTop]=0;
		return ;
	}
	//char nowFileName[12];
	//int road[100];//层数限制100层
	//int nowRoadNum;
	int inodeIndex=findFileInodeIndex(fileName);
	INode inode0;
	superBlock.getINodeFromDisk(&inode0,inodeIndex);
	if(inodeIndex==-1){
		printf("The directory is not found!\n");
	}else
	{
		int j;
		char fileName2[20];int tempIndex=0;
		for(j=strlen(fileName)-1;j>=0;j--){
			if(fileName[j]=='/')break;
		}
		for(int i=j+1;i<strlen(fileName);i++)
		{
			fileName2[tempIndex++]=fileName[i];
		}
		fileName2[tempIndex]='\0';
		if(inode0.IsDiretory()){
			memcpy(nowFileName,fileName2,strlen(fileName2)+1);
			if (fileName[0]=='/')
			{
				char strTem[20]="";int tIndex=0;
				int indexOfFileName=1;
				nowRoadStackTop=1;
				for(;indexOfFileName<strlen(fileName);indexOfFileName++){
					if (fileName[indexOfFileName]!='/')
					{
						strTem[tIndex++]=fileName[indexOfFileName];
					}else{
						strTem[tIndex]='\0';
						tIndex=0;
						direArray[nowRoadStackTop++]=strTem;
					}
				}
				strTem[tIndex]='\0';
				tIndex=0;
				direArray[nowRoadStackTop++]=strTem;
				return ;
			}else{
				direArray[++nowRoadStackTop]=fileName;
				roadStack[nowRoadStackTop]=inodeIndex;
				return;
			}
		}else
		{
			printf("The file name isn't a directory!");
			return;
		}
	}
}

void FileSystem::find(char *filename)
{
	int inodeIndex=findFileInodeIndex(filename);
	if(inodeIndex==-1){
		printf("The file is not found!\n");
	}else
	{
		int j;
		char fileName2[20];int tempIndex=0;
		for(j=strlen(filename)-1;j>=0;j--){
			if(filename[j]=='/')break;
		}
		for(int i=j+1;i<strlen(filename);i++)
		{
			fileName2[tempIndex++]=filename[i];
		}
		fileName2[tempIndex]='\0';
		INode inode0;
		superBlock.getINodeFromDisk(&inode0,inodeIndex);
		int year,month,dar,hour,minutes;
		inode0.getTime(&year,&month,&dar,&hour,&minutes);
		printf("%-12s%-6d%-10s%4d/%02d/%02d %02d:%02d\n",fileName2,
			inode0.FileSize(),inode0.IsDiretory()?"Directory":"File",
			year,month,dar,hour,minutes);
	}
}

void FileSystem::createFile(char *filename,int fileSize)
{
	////////////查找到是否存在
	int InodeIndexTemp=findFileInodeIndex(filename);//找到filename
	if(InodeIndexTemp!=-1){
		INode inode0;
		superBlock.getINodeFromDisk(&inode0,InodeIndexTemp);
		if(!inode0.IsDiretory()){
			printf("The file already is exitting!\n");
			return ;//如果是目录则返回
		}
	}
	///////////

	if(fileSize>SETTING_FILE_MAX_SIZE){ //大于size
		printf("The file is too big!System's max file size is %d B.\n",SETTING_FILE_MAX_SIZE);
	}
	int nowINodeIndex = roadStack[nowRoadStackTop];
	if(filename[0]=='/')
	{
		nowINodeIndex=findFileInodeFaIndex(filename);
	}
	INode inodeTemp;
	superBlock.getINodeFromDisk(&inodeTemp,nowINodeIndex);
	if(!inodeTemp.IsDiretory()){printf("Can not make dir in file!");return;}

	if(inodeTemp.FileSize()>=1024){printf("There is no place for new directory!");return;}

	MyDirectory newDir;

	newDir.setName(filename);
	int newINodeIndex=superBlock.allocNewINode();

	string strTemp=filename;

	int temp=0;
	for(int i=strlen(filename);i<fileSize;i++)
	{
		strTemp+=('0'+temp);
		temp++;
		temp%=10;
	}

	int size=fileSize;
	INode inodeTemp2;
	inodeTemp2.BlockNum((1023+size)/1024);
	inodeTemp2.FileSize(size);
	inodeTemp2.Group(userGroup);

	for(int i=0;i<=((size-1)/1024);i++)
	{
		int nowBlockNum;
		if(i<20)
		{
			nowBlockNum=inodeTemp2.DirectAdd()[i]=superBlock.allocNewBlock();
		}else
		{
			int inDirectBlockNum;
			if (inodeTemp2.IndirectAdd()==-1)
			{
				inDirectBlockNum=superBlock.allocNewBlock();
				inodeTemp2.IndirectAdd(inDirectBlockNum);
			}
			inDirectBlockNum=inodeTemp2.IndirectAdd();
			Block nowBlock;//

			//将块号写入block
			//获取Block   写入Block   写回硬盘
			superBlock.getBlockFromDisk(&nowBlock,inDirectBlockNum);
			//获取新的block号
			nowBlockNum = superBlock.allocNewBlock();
			memcpy(nowBlock.blockArray+4*(i-20),&nowBlockNum,4);
			superBlock.writeBlockToDisk(&nowBlock,inDirectBlockNum);
		}

		Block nowBlockFile;//目前的block
		for(int j=0;(j<1024)&(j<size-i*1024);j++)
		{
			nowBlockFile.blockArray[j]=strTemp[j+i*1024];
		}
		superBlock.writeBlockToDisk(&nowBlockFile,nowBlockNum);
	}

	inodeTemp2.IsDiretory(false);
	inodeTemp2.Owner(userName);
	//INode写回
	superBlock.writeINodeToDisk(&inodeTemp2,newINodeIndex);

	newDir.setIndex(newINodeIndex);
	newDir.setFatherName(nowFileName);
	newDir.setFaIndex(nowINodeIndex);

	Block blockTemp;
	superBlock.getBlockFromDisk(&blockTemp,inodeTemp.DirectAdd()[0]);
	memcpy(blockTemp.blockArray+inodeTemp.FileSize(),&newDir,sizeof(newDir));
	superBlock.writeBlockToDisk(&blockTemp,inodeTemp.DirectAdd()[0]);

	//父节点修改大小
	inodeTemp.FileSize(inodeTemp.FileSize()+32);
	superBlock.writeINodeToDisk(&inodeTemp,nowINodeIndex);
}


//删除某个文件
void FileSystem::deleteFile(char *filename)
{
	int nowINodeIndex;
	nowINodeIndex=findFileInodeIndex(filename);//找到文件的inode
	if(nowINodeIndex==-1){printf("The file not find!\n");return;}
	INode inodeWantToDelete;//删除的Inode
	superBlock.getINodeFromDisk(&inodeWantToDelete,nowINodeIndex);
	if(inodeWantToDelete.IsDiretory()){printf("The file is directory,not file!\n");return ;}

	//获取这个Inode对应的block
	Block block0;
	//获取这个Inode对应的size
	int fileSize=inodeWantToDelete.FileSize();
	for(int numB=0;numB<inodeWantToDelete.BlockNum();numB++){
		int nowBlockNum;
		if(numB<20)
		{
			nowBlockNum=inodeWantToDelete.DirectAdd()[numB];
		}else
		{
			int inDirectBlockNum;
			inDirectBlockNum=inodeWantToDelete.IndirectAdd();
			Block nowBlock;
			superBlock.getBlockFromDisk(&nowBlock,inDirectBlockNum);
			memcpy(&nowBlockNum,nowBlock.blockArray+4*(numB-20),4);
		}
		superBlock.freeBlock(nowBlockNum);
	}
	//如果是空的也要删除第一个块   这个块会被创建
	if (inodeWantToDelete.BlockNum()==0)
	{
		superBlock.freeBlock(inodeWantToDelete.DirectAdd()[0]);
	}
	if (inodeWantToDelete.IndirectAdd()!=-1)
	{
		superBlock.freeBlock(inodeWantToDelete.IndirectAdd());
	}

	//更新文件所在目录
	//把文件按顺序向前移动
	//nowINodeIndex
    int indexFa = findFileInodeFaIndex(filename);
	INode inodetemp2;//
	superBlock.getINodeFromDisk(&inodetemp2,indexFa);
	Block blockTemp2;
	superBlock.getBlockFromDisk(&blockTemp2,inodetemp2.DirectAdd()[0]);
	MyDirectory dir2;
	for(int i=0;i<1024;i+=32)
	{
		memcpy(&dir2,&(blockTemp2.blockArray[i]),sizeof(dir2));
		if(dir2.Index()==nowINodeIndex){
			for(int j=i;j+32<1024;j++)
			{//////////////////////////////////////////////////////////////////////
				blockTemp2.blockArray[j]=blockTemp2.blockArray[j+32];
			}
			break;
		}
	}
	superBlock.writeBlockToDisk(&blockTemp2,inodetemp2.DirectAdd()[0]);
	inodetemp2.FileSize(inodetemp2.FileSize()-32);
	superBlock.writeINodeToDisk(&inodetemp2,indexFa);
	superBlock.freeINode(nowINodeIndex);
}

void FileSystem::cat(char *filename)
{
	int nowINodeIndex = roadStack[nowRoadStackTop];
	nowINodeIndex=findFileInodeIndex(filename);
	printFile(nowINodeIndex);
}

void FileSystem::cp(char *desFilename,char *srcFilename)
{
	deleteFile(desFilename);
	createFile(desFilename,100);
}

void FileSystem::chmod(char *filename,int mod)
{

}

void FileSystem::chown(char *filename,char* toOwner)
{

}

void FileSystem::chgrp(char *fileName,char* toGroup)
{

}

void FileSystem::chnam(char *filename,char* toFileName)
{

}

void FileSystem::sum()
{
	//□□■■
	double lessBlockKB=superBlock.FreeBlockStackTop()+1;
	double BlockKB=1024*15;
	double lessBlockPercent=lessBlockKB/BlockKB;

	double lessINodeKB=(128.0/1024.0)*(superBlock.FreeINodeStackTop()+1);
	double INodeKB=128;
	double lessINodePercent=lessINodeKB/INodeKB;


	double totalLessKB=lessBlockKB+lessINodeKB;
	double totalKB=BlockKB+INodeKB;
	double totalLessPercent=totalLessKB/totalKB;

	int numTotalNotFree=totalLessPercent*20;
	int numOfBlockNotFree=lessBlockPercent*20;
	int numOfINodeNotFree=lessINodePercent*20;

	printf("Total:");
	for(int i=0;i<20-numTotalNotFree;i++)
		printf("■");
	for(int i=0;i<numTotalNotFree;i++)
		printf("□");
	printf("%.2lfKB/%.2lfKB(Used/Total)\n",totalKB-totalLessKB,totalKB);

	printf("Block:");
	for(int i=0;i<20-numOfBlockNotFree;i++)
		printf("■");
	for(int i=0;i<numOfBlockNotFree;i++)
		printf("□");
	printf("%.2lfKB/%.2lfKB(Used/Total)\n",BlockKB-lessBlockKB,BlockKB);

	printf("INode:");
	for(int i=0;i<20-numOfINodeNotFree;i++)
		printf("■");
	for(int i=0;i<numOfINodeNotFree;i++)
		printf("□");
	printf("%.2lfKB/%.2lfKB(Used/Total)\n",INodeKB-lessINodeKB,INodeKB);
}

//-1是找不到   其他是找到了
int FileSystem::findFileInodeIndex(char* filename)
{
	if(filename[0]=='/')
	{
		bool isContinue=true;
		char nowCheckFileName[20];
		int nowCheckFileNameIndex=0;
		int indexOfFileName=1;
		while(filename[indexOfFileName]!='/'&indexOfFileName!=strlen(filename))
		{
			nowCheckFileName[nowCheckFileNameIndex++]=filename[indexOfFileName++];
		}
		if(indexOfFileName==strlen(filename))isContinue=false;
		nowCheckFileName[nowCheckFileNameIndex]='\0';
		INode inode0;
		Block block0;
		int nowInodeIndex=0;
		superBlock.getINodeFromDisk(&inode0,nowInodeIndex);
		superBlock.getBlockFromDisk(&block0,inode0.DirectAdd()[0]);

		//遍历
		int fileSize=inode0.FileSize();
		MyDirectory dir;
		int i;
		for(i=0;i<fileSize;i+=32)
		{
			memcpy(&dir,block0.blockArray+i,sizeof(dir));

			if(!strcmp(nowCheckFileName,dir.Name())){

				superBlock.getINodeFromDisk(&inode0,dir.Index());
				int year,month,dar,hour,minutes;
				inode0.getTime(&year,&month,&dar,&hour,&minutes);
				if(isContinue==false)
					return dir.Index();
				nowInodeIndex=dir.Index();
				break;
			}
		}
		if(i>=fileSize){isContinue=false;return -1;}

		while(isContinue){
			////////////////////////////////////!!!!!!!!!
			if(!inode0.IsDiretory())
			{
				return -1;
			}
			indexOfFileName++;
			nowCheckFileNameIndex=0;
			while(filename[indexOfFileName]!='/'&indexOfFileName!=strlen(filename))
			{
				nowCheckFileName[nowCheckFileNameIndex++]=filename[indexOfFileName++];
			}
			if(indexOfFileName==strlen(filename))isContinue=false;
			nowCheckFileName[nowCheckFileNameIndex]='\0';

			Block block0;
			superBlock.getBlockFromDisk(&block0,inode0.DirectAdd()[0]);

			//遍历
			int fileSize=inode0.FileSize();
			MyDirectory dir;
			int i;
			for(i=0;i<fileSize;i+=32)
			{
				memcpy(&dir,block0.blockArray+i,sizeof(dir));
				if(!strcmp(nowCheckFileName,dir.Name())){
					superBlock.getINodeFromDisk(&inode0,dir.Index());
					if(isContinue==false)
						return dir.Index();	
					nowCheckFileNameIndex=dir.Index();
					break;
				}
			}
			if(i>=fileSize){isContinue=false;return -1;}
		}
	}
	else
	{
		bool isContinue=true;
		char nowCheckFileName[20];
		int nowCheckFileNameIndex=roadStack[nowRoadStackTop];
		int indexOfFileName=0;
		while(filename[indexOfFileName]!='/'&indexOfFileName!=strlen(filename))
		{
			nowCheckFileName[nowCheckFileNameIndex++]=filename[indexOfFileName++];
		}
		if(indexOfFileName==strlen(filename))isContinue=false;
		nowCheckFileName[nowCheckFileNameIndex]='\0';
		INode inode0;
		Block block0;
		int nowInodeIndex=0;
		superBlock.getINodeFromDisk(&inode0,nowInodeIndex);
		superBlock.getBlockFromDisk(&block0,inode0.DirectAdd()[0]);

		//遍历
		int fileSize=inode0.FileSize();
		MyDirectory dir;
		int i;
		for(i=0;i<fileSize;i+=32)
		{
			memcpy(&dir,block0.blockArray+i,sizeof(dir));

			if(!strcmp(nowCheckFileName,dir.Name())){

				superBlock.getINodeFromDisk(&inode0,dir.Index());
				int year,month,dar,hour,minutes;
				inode0.getTime(&year,&month,&dar,&hour,&minutes);
				if(isContinue==false)
					return dir.Index();
				nowInodeIndex=dir.Index();
				break;
			}
		}
		if(i>=fileSize){isContinue=false;return -1;}


		while(isContinue){
			////////////////////////////////////!!!!!!!!!
			if(!inode0.IsDiretory())
			{
				return -1;
			}
			indexOfFileName++;
			nowCheckFileNameIndex=0;
			while(filename[indexOfFileName]!='/'&indexOfFileName!=strlen(filename))
			{
				nowCheckFileName[nowCheckFileNameIndex++]=filename[indexOfFileName++];
			}
			if(indexOfFileName==strlen(filename))isContinue=false;
			nowCheckFileName[nowCheckFileNameIndex]='\0';

			Block block0;
			superBlock.getBlockFromDisk(&block0,inode0.DirectAdd()[0]);

			//遍历
			int fileSize=inode0.FileSize();
			MyDirectory dir;
			int i;
			for(i=0;i<fileSize;i+=32)
			{
				memcpy(&dir,block0.blockArray+i,sizeof(dir));
				if(!strcmp(nowCheckFileName,dir.Name())){
					superBlock.getINodeFromDisk(&inode0,dir.Index());
					if(isContinue==false)
						return dir.Index();	
					nowCheckFileNameIndex=dir.Index();
					break;
				}
			}
			if(i>=fileSize){isContinue=false;return -1;}
		}
	}
	return -1;
}


void FileSystem::printFile(int inodeIndex)
{
	INode fileINode;
	superBlock.getINodeFromDisk(&fileINode,inodeIndex);
	if(fileINode.IsDiretory()){printf("The the file is a directory!\n");return;}

	int size=fileINode.FileSize();
	for(int i=0;i<=((size-1)/1024);i++)
	{
		int nowBlockNum;
		if(i<20)
		{
			nowBlockNum=fileINode.DirectAdd()[i];
		}else
		{
			int inDirectBlockNum;

			inDirectBlockNum=fileINode.IndirectAdd();
			Block nowBlock;
			superBlock.getBlockFromDisk(&nowBlock,inDirectBlockNum);
			memcpy(&nowBlockNum,nowBlock.blockArray+4*(i-20),4);
		}
		Block nowBlockFile;
		superBlock.getBlockFromDisk(&nowBlockFile,nowBlockNum);
		for(int j=0;(j<1024)&(j<size-i*1024);j++)
		{
			printf("%c",nowBlockFile.blockArray[j]);
		}
	}
	printf("\n");
}


void FileSystem::printNowRoad(void)
{
	printf("/root");
	for(int i=1;i<=nowRoadStackTop;i++){

	}
	printf(">");
}

//返回-1就是没有找到  其他就是Index的数字
int FileSystem::findFileInodeFaIndex(char * filename)
{
	if(filename[0]=='/')                 //如果是绝对路径
	{
		bool isContinue=true;            //是否找到
		char nowCheckFileName[20];       //现在查找的那个名字
		int nowCheckFileNameIndex=0;
		int indexOfFileName=1;
		while(filename[indexOfFileName]!='/'&indexOfFileName!=strlen(filename))
		{
			nowCheckFileName[nowCheckFileNameIndex++]=filename[indexOfFileName++];
		}
		if(indexOfFileName==strlen(filename))isContinue=false;
		nowCheckFileName[nowCheckFileNameIndex]='\0';
		INode inode0;
		Block block0;
		int nowInodeIndex=0;             //当前是0路径
		superBlock.getINodeFromDisk(&inode0,nowInodeIndex);
		superBlock.getBlockFromDisk(&block0,inode0.DirectAdd()[0]);

		//遍历该目录的文件dir
		int fileSize=inode0.FileSize();
		MyDirectory dir;
		int i;
		for(i=0;i<fileSize;i+=32)
		{
			memcpy(&dir,block0.blockArray+i,sizeof(dir));
			if(!strcmp(nowCheckFileName,dir.Name())){
				superBlock.getINodeFromDisk(&inode0,dir.Index());
				if(isContinue==false)
					return nowInodeIndex;
				nowInodeIndex=dir.Index();
				break;
			}
		}
		if(i>=fileSize){isContinue=false;return -1;}
		while(isContinue){
			////////////////////////////////////!!!!!!!!!
			if(!inode0.IsDiretory())
			{
				return -1;
			}
			indexOfFileName++;
			nowCheckFileNameIndex=0;
			while(filename[indexOfFileName]!='/'&indexOfFileName!=strlen(filename))
			{
				nowCheckFileName[nowCheckFileNameIndex++]=filename[indexOfFileName++];
			}
			if(indexOfFileName==strlen(filename))isContinue=false;
			nowCheckFileName[nowCheckFileNameIndex]='\0';

			Block block0;
			superBlock.getBlockFromDisk(&block0,inode0.DirectAdd()[0]);

			//遍历
			int fileSize=inode0.FileSize();
			MyDirectory dir;
			int i;
			for(i=0;i<fileSize;i+=32)
			{
				memcpy(&dir,block0.blockArray+i,sizeof(dir));
				if(!strcmp(nowCheckFileName,dir.Name())){
					superBlock.getINodeFromDisk(&inode0,dir.Index());
					if(isContinue==false)
						return nowInodeIndex;	
					nowInodeIndex=dir.Index();
					break;
				}
			}
			if(i>=fileSize){isContinue=false;return -1;}
		}
	}
	else
	{
		return 0;
	}
	return -1;
}
