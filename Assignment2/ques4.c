/*Try and find the invalid flags combinations for Open() system call.*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

	int fd;
	
	//fd = open("text.txt",O_RDONLY, 0600 );
	//fd = open("text.txt",O_WRONLY, 0600 );
	//fd = open("text.txt",O_RDWR, 0600 );
	//fd = open("text.txt",O_DIRECTORY, 0600 );
	//fd = open("text.txt",O_RDONLY | O_TRUNC, 0600 );
	//fd = open("text.txt",O_WRONLY | O_TRUNC , 0600 );
	fd = open("text.txt",O_RDWR | O_TRUNC , 0600 );

	if(fd == -1){
		perror("file not exist\n");
		exit(1);
	}

	else{
		printf("file present\n");
	
	}

	close(fd);
	return 0;
}

