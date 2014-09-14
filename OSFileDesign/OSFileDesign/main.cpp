#include"head.h"
#include "FileSystem.h"
#include "MyDirectory.h"
FileSystem fileSystem;
int main()
{	

//	system("pause");
	fileSystem.welcome();
	if(fileSystem.login()){
		getchar();
		fileSystem.getCommand();
	}
	printf("EXIT");
}