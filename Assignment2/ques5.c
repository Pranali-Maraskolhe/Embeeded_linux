/*Write a C program to Open a file in appropriate mode and write the user entered contents into it.*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

	int fd;
	char data[100];
	ssize_t wr;

	fd = open("test.txt",O_WRONLY,0600);

	if(fd == -1){
		perror("file not present");
		exit(1);
	}

	else{
		printf("Enter data into file: ");
		scanf("%[^\n]s",data);
		wr = write(fd,data,strlen(data));

		if(wr == -1){
			perror("data has not been writtren\n");
			exit(1);
		}
		else{
			printf("data has written\n");
		}
	}
	
	close(fd);
	
	return 0;
}
