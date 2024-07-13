#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){

	int fd;
	char data[100];
        ssize_t	nr;

	fd = open("nishu.txt", O_RDONLY, 0400);

	if(fd < 0){
		perror("File does not present\n");
	}

	else{
		nr = read(fd,data,sizeof(data));

		if(nr == -1){
			printf("Data not present\n");
			exit(1);
		} 

		else{
			printf("%s",data);
		}
	}

	close(fd);
	return 0;
}
