//#include "pipex.h"
#include "../include/pipex.h"
#include <stdio.h>
#include <unistd.h>

void	pipex(int argc, char *argv[], char *envp[])
{
  int i;
  int fd[2];
  pid_t pid;

  char  **arg;
  char  *cmd;
  int flag;

	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
  {
    ft_printf("er num=%d\n", ENOENT);
		strerror(ENOENT);
    perror(argv[1]);
		exit(ENOENT);
  }
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);

	i = -1;
    while (++i < argc - 3)
	{
		pipe(fd);
		if (i == argc - 4)
		{
			close(fd[1]);
			fd[1]  = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		}
        pid = fork();
		if (pid == 0) // child
		{
     // exit(127);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
      arg = ft_split(argv[i + 2], ' ');
      cmd = ft_strjoin("/bin/", *arg);
			execve(cmd, arg, envp);
      perror("execve"); 
      exit(42);
		}
		else if (pid > 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
    else
     perror("fork");
  }
  
  flag = 11;
	waitpid(pid, &flag, 0);
//	waitpid(pid[2], NULL, 0);
/*  if (flag == 127)
    write(2, "error 127\n", 10);
  else
    write(2, "error != 127\n", 14);
*/
  exit (flag);

}

int	main(int argc, char *argv[], char *envp[])
{
 //   char *cat = "/bin/cat";
  //  char *args[] = { "cat", NULL };
  //   char *sleep = "/bin/cat";
  //

  pipex(argc, argv, envp);

//	write(2, "end\n", 4);
//	while (1)
//		;
	exit (24);
}
