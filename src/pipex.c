/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:35:22 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/16 18:05:38 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_execve(char *cmd, char **arg)
{
	if (arg)
		ft_free_char2d(arg);
	if (cmd)
		free(cmd);
	write(2, "zsh: command not found: ", 24);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	child_process(t_pipex *ppx, int fd[2], int i)
{
	char	**arg;
	char	*cmd;

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
	cmd = make_cmd(ppx, *arg);
	execve(cmd, arg, ppx->envp);
	free_execve(cmd, arg);
	exit(127);
}

void	parent_process(int fd[2])
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	pipex(t_pipex *ppx)
{
	int	i;
	int	fd[2];
	int	status;

	i = -1;
	while (++i < ppx->argc - 3)
	{
		pipe(fd);
		if (i == ppx->argc - 4)
		{
			close(fd[1]);
			fd[1] = ppx->fd_out;
		}
		ppx->pids[i] = fork();
		if (ppx->pids[i] == 0)
			child_process(ppx, fd, i);
		else if (ppx->pids[i] > 0)
			parent_process(fd);
		else
			perror("Fork");
	}
	while (--i > 0)
		waitpid(ppx->pids[i], &status, 0);
	return ((status & 0xff00) >> 8);
}
