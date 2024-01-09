#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int pipe_fun(void)
{
    int fd[2];
    pid_t pid;
    char buffer[14];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fd[0]);
        write(fd[1], "Hello parent!", 13);
        close(fd[1]); 
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, 13);
        close(fd[0]);
        printf("Message from child: ->%s<-\n", buffer);
    }
	
	return (0);
}

int main()
{
	pipe_fun();
	pipe_fun();

	while (1)
	{
	}
	return (0);
}

/*
int main()
{
    int fd[2];
    int fd2[2];
    pid_t pid;
    pid_t pid2;
    char buffer[14];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        close(fd[0]);
        write(fd[1], "Hello parent!", 13);
        close(fd[1]); 
    }
    else
    {
        close(fd[1]);
        read(fd[0], buffer, 13);
        close(fd[0]);
        printf("Message from child: ->%s<-\n", buffer);
    }

	
    if (pipe(fd2) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
    {
        close(fd2[0]); // close the read end of the pipe
        write(fd2[1], "Hello parent!", 13);
        close(fd2[1]); // close the write end of the pipe
    }
    else
    {
        close(fd2[1]); // close the write end of the pipe
        read(fd2[0], buffer, 13);
        close(fd2[0]); // close the read end of the pipe
        printf("Second fork msg from child: ->%s<-\n", buffer);
    }
	while (1)
	{
	}

	return (0);

}
*/

