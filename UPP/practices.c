#include "practices.h"
#include <dirent.h>
void lsdirectory(char* dir)
{
	if(dir == NULL) 
	{
		printf("Directory can't be empty string!\n");
		return;
	}
	DIR* dp;
	struct dirent* dirp;
	if((dp = opendir(dir)) == NULL)
	{
		printf("Can't open directory!\n");
		return;
	}
	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	exit(0);
}


int main(int argc, char *argv[])
{
	lsdirectory("/Users/ht");
}
