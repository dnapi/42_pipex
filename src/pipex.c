//#include "pipex.h"
#include "../include/pipex.h"
#include <unistd.h>

char	*make_cmd(t_pipex *ppx, char *cmd_name)
{
	char	*cmd;
	char	*cmd_temp;
	int		i;

	i = -1;
	if (access(cmd_name, F_OK | X_OK) == 0)
			return (cmd_name);
	while (ppx->paths[++i])
	{
		cmd_temp = ft_strjoin(ppx->paths[i], "/");
		cmd = ft_strjoin(cmd_temp, cmd_name);
		free(cmd_temp);
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
	}
	free(cmd);
	cmd = ft_strdup(cmd_name);
	return (cmd);
}

void child_process(t_pipex *ppx, int fd[2], int i)
{
	char  **arg;
	char  *cmd;

	if (!i && ppx->fd_in == -1)
		exit (1);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	cmd = ppx->argv[i + 2];
	if (access(cmd, F_OK | X_OK) == 0 || ft_strchr(cmd, '\''))
	{
		arg = (char **)malloc(sizeof(char *) * 2);
		arg[0] = ft_strdup(cmd);
		arg[1] = NULL;
	}
	else
		arg = ft_split(cmd, ' ');
//	arg = get_args(ppx->argv[i + 2]);
	cmd = make_cmd(ppx, *arg);
// make if condition for error case if execve == -1  clean all
	execve(cmd, arg, ppx->envp);
	//perror(cmd);
	if (arg)
		ft_free_char2d(arg);
	if (cmd)
		free(cmd);
	write(2, "zsh: command not found: ", 24);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(127);
}

void parent_process(int fd[2])
{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
}

int	pipex(t_pipex *ppx)
{
	int	i;
	int	fd[2];
	pid_t	pid;
	int status;

	i = -1;
    while (++i < ppx->argc - 3)
	{
		pipe(fd);
		if (i == ppx->argc - 4)
		{
			close(fd[1]);
			fd[1] = ppx->fd_out;
		}
        pid = fork();
		if (pid == 0)
			child_process(ppx, fd, i);
		else if (pid > 0)
			parent_process(fd);
		else
			perror("Fork");
	}
//	waitpid(pid, &status, 0);
// use array of pids to get the status of last process	
	while (wait(&status) > 0)
		;
	
	return ((status & 0xff00) >> 8);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*ppx;
	int	status;

	if (argc < 5)
		return (1);

	status = 0;
	ppx = init_pipex(argc, argv, envp);
	if (ppx->fd_out == -1)
	{
		if (ppx->paths)
	        ft_free_char2d(ppx->paths);
	    return (1);
	}
	dup2(ppx->fd_in, STDIN_FILENO);
	status = pipex(ppx);
	if (ppx->paths)
		ft_free_char2d(ppx->paths);
  
// while (1)
  // ;

	return (status);
}
