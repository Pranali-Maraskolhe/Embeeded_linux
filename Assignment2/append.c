#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main() {
	
	int fd;
	char data[100];
	char data1[100];
	ssize_t wr;
	ssize_t nr;

	fd = open("nishu.txt", O_APPEND | O_WRONLY | O_RDONLY, 0600);

	if(fd == -1) {
		perror("file not exists\n");
	}

	else{
		printf("\nEnter data in file\n");
		scanf("\n %[^\n]s \n",data);
		
		wr = write(fd,data,strlen(data));

		if(wr == -1) {
			printf("data not writtern\n");
		}
		else{
			printf("data writtern sucessfully\n");
		}
	}

	close(fd);
	return 0;
}
