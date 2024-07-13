/*Write a C program to open a file using file I/O in readonly mode using required flags. Read the contents
of the file and display it on the screen. After displaying the contents close the file.*/


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
	ssize_t nr;

	fd = open("text.txt", O_RDONLY, 0400);

	if(fd == -1){
		perror("File not present");
		exit(1);
	}
	/*else{
		printf("Enter the data: ");
		scanf("%s",data);
		wr = write(fd,data,strlen(data));
		if(wr == -1){
			perror("data present");
			exit(1);
		}*/
	else{
		
		nr = read(fd,data,sizeof(data));
		printf("Total number of lines are = %ld \n",nr);

		if(nr == -1){
			perror("data not found");
			exit(1);
		}
		else{
			//data[nr] = '\0';
			printf("%s",data);
		}
	}
		


	close(fd);

	return 0;
}

