#include "pipex.h"
#include "errno.h"

int	main(int argc, char *argv[], char *envp[])
{
    int num = 3;
	int	i;
	int		fd_file;
	int		fd[2];
	pid_t	pid[5];
    char *cat = "/bin/cat";
    char *args[] = { "cat", NULL };
//   char *sleep = "/bin/cat";
//   char *args_sleep[] = { "sleep", "2",  NULL };

	fd_file = open(argv[1], O_RDONLY);
	if (fd_file == -1)
		strerror(ENOENT);
	dup2(fd_file, STDIN_FILENO);
	close(fd_file);
	(void) envp;

	i = -1;
    while (++i < num)
	{
		pipe(fd);
		if (i == num - 1)
		{
			close(fd[1]);
			fd[1]  = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
        pid[i] = fork();
		if (pid[i] == 0) // child
		{
			write(2, "start\n", 6);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
//			sleep(25);
			execve(cat, args, NULL);
			write(2, "end\n", 4);
            exit(0);
		}
		else if (pid[i] > 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
        else // fork error 
		{
            perror("fork");
            return 1;
        }
    }


	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);

	write(2, "end\n", 4);
//	while (1)
//		;
	exit (0);
}
