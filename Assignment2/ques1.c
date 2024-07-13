/*Using file I/O , Open a .txt file (if present already) ,create it if it is not already present. Check whether
the file has opened successfully or not. Close it. (Write necessarry observations and flags usage)*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	

	int fd;
	char filename1[200] ="/home/pranali/linux_files/Assignment2/" ;
	char filename[100];
	printf("Enter filename: ");
	scanf("%s",filename);
	strcat(filename1,filename);
	printf("%s\n",filename1);
	fd = open(filename1, O_WRONLY,0600);

	if(fd < 0){
		perror("File is not present\n");
		fd = open(filename1, O_CREAT | O_WRONLY,0600);
		if(fd < 0)
		{
			perror("can't create\n");
			exit(1);
		}
		else{
			printf("Created successfully\n");
		}


	}
	else {

		printf("present\n");
		exit(1);
	}
	
	
		close(fd);

	return 0;
}
