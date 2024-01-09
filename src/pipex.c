#include "pipex.h"
#include "errno.h"

int	main(int argc, char *argv[], char *envp[])
{
    int num_processes = 3;
	int	i;
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int	fd[2];
    char *cat = "/bin/cat";
    char *args[] = { "cat", NULL };


//	printf("in=%s, out = %s \n", argv[1], argv[argc - 1]);
//	exit (0);

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		strerror(ENOENT);
	fd_out = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(fd_in, 0);
	dup2(fd_out, 1);

	(void) envp;

//	execve(cat, args, NULL);
//	exit (0);
//	ft_printf("envp[0]=->%s<-\n",envp[0]);
	i = -1;
    while (++i < num_processes) 
	{
		pipe(fd);
        pid = fork();

		if (pid > 0)
		{
        	waitpid(pid, NULL, 0);
			close(fd[1]);
			dup2(fd[0], 0);
            ft_printf("Hi from parent? %d: My PID is %d\n", i + 1, getpid());
			ft_printf("I am parent. Just stoped waiting for pid=%d\n", pid);
			close(fd[0]);
		}
		else if (pid == 0) // child
		{
			close(fd[0]);
			dup2(fd[1], 1);
            ft_printf("Child i=%d: My PID is %d\n", i + 1, getpid());
			execve(cat, args, NULL);
			close(fd[1]);
//			sleep(5);
            exit(0);
		}
        else // fork error 
		{
            perror("fork");
            return 1;
        }
    }
	dup2(fd_out, 1);
	ft_printf("Parent: no more children! i+1=%d: My PID is %d\n", i + 1, getpid());
	execve(cat, args, NULL);

	while (1)
	{
	}
	exit (0);
}
