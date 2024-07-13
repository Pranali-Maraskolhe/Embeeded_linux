#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	
	int fd;
	char data[100];
	ssize_t wr;

	fd = open("pranali.txt", O_WRONLY, 0200);

	if(fd < 0){
		perror("file not exists");
		exit(1);
	}

	else{
		printf("Enter data: \n");
		scanf("%[^\n]s",data);
		
		wr = write(fd,data,strlen(data));

		if(wr == -1){
			printf("data not present\n");
			exit(1);
		}

		else{
			printf("data writtren succesfully");
		}
	}

	close(fd);
	return 0;
}
