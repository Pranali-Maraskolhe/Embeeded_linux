#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main() {

	int fd;
	char path[200] = "/home/pranali/linux_files/Assignment2";
	char filename[200];
	printf("Enter the name of file: ");
	scanf("%s",filename);
	strcat(path,filename);

	fd = open(filename, O_WRONLY, 0600);

	if(fd < 0){
		perror("File not present\n");

		fd = open(filename, O_CREAT, 0600);

		if(fd > 0){
			printf("File created sucessfully\n");
		}
		else{
			perror("File not created");
		}

	}

	else{
		printf("File Present %s\n",filename);
	}

	close(fd);

	return 0;


}
