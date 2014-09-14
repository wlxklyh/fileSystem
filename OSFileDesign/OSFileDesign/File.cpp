#include "File.h"
#include <string.h>


char* File::getName(){
	return name;
}

void File::setName(char* name){
	strcpy(this->name,name);
}