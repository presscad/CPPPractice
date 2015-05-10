#include "practices.h"
#include <dirent.h>
void lsdirectory(char* dir)
{
	if(dir == NULL) return;
	DIR* dp;
	struct dirent* dirp;
	if((dp = opendir(dir)) == NULL)
		return;
	while((dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);
	closedir(dp);
	exit(0);
}


int main(int argc, char *argv[])
{
	lsdirectory("/Users/ht");
}
