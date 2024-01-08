#include "pipex.h"
#include "errno.h"

int	main(int argc, char *argv[], char *envp[])
{
    int num_processes = 2;
	int	i;
	int		fd1;
	int		fd2;
	pid_t	pid;
	int	fd[2];

	pipe(fd);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 == -1)
		strerror(ENOENT);
	fd2 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 644);

	(void) envp;
//	ft_printf("envp[0]=->%s<-\n",envp[0]);
	i = -1;
    while (++i < num_processes) 
	{
        pid = fork();

        if (pid == 0) 
		{
            ft_printf("Child %d: My PID is %d\n", i + 1, getpid());
			close(fd[0]);
			write(fd[1], "Hi from child\n", 14);
			close(fd[1]);
            exit(0);
		}
		else if (pid > 0)
		{
        	wait(NULL);
            ft_printf("Hi from parent? %d: My PID is %d\n", i + 1, getpid());
			ft_printf("pid=%d\n", pid);
		}
        else 
		{
            perror("fork");
            return 1;
        }
    }
	ft_printf("Hi from parent? %d: My PID is %d\n", i + 1, getpid());
	ft_printf("pid=%d\n", pid);
	while (1)
	{
	}
    // Wait for all child processes to complete
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }
	return (0);
}
