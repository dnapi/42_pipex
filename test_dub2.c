#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
 
int main()
{
	int fd;
	int fd2[2];

	fd = open("example.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd, 1);
	close(fd);
	printf("This is printed in example.txt!\n");
	pipe(fd2);
	printf("fd2=%d,%d\n", fd2[0], fd2[1]);
 
	return (0);
}
