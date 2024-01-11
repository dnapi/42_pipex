//#include "pipex.h"
#include "../include/pipex.h"
#include <unistd.h>
//#include <stdio.h>
//#include <unistd.h>

int	pipex(int argc, char *argv[], char *envp[])
{
	int	i;
	int	fd[2];
	pid_t	pid;

  char  **arg;
  char  *cmd;
  int flag;
  int flag_w;

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
     // exit(127);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
      arg = ft_split(argv[i + 2], ' ');
      cmd = ft_strjoin("/bin/", *arg);
			(void)arg;
			(void)cmd;
			(void)envp;
//			execve(cmd, arg, envp);
  //    perror("execve");
//			sleep(5);
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
	flag_w = waitpid(pid, &flag, 0);
	ft_printf("flag_w=%d\n",flag_w);
	ft_printf("flag=%d\n",flag);

  return (flag);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;
 //   char *cat = "/bin/cat";
  //  char *args[] = { "cat", NULL };
  //   char *sleep = "/bin/cat";
  //

  status = pipex(argc, argv, envp);

//	write(2, "end\n", 4);
//	while (1)
//		;
	return (status);
}
