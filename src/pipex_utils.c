/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 06:33:46 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/17 13:44:01 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_path_defined(char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (i);
	}
	return (-1);
}

void	set_path_pipex(t_pipex *pnt, char *envp[])
{
	int		pos;
	char	*str_path;

	pos = -1;
	if (envp && *envp)
		pos = is_path_defined(envp);
	if (pos > -1 && *envp)
	{
		str_path = ft_strjoin(envp[pos] + 5, \
					":/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	}
	else
		str_path = ft_strdup(":/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!str_path)
		return ;
	pnt->paths = ft_split(str_path, ':');
	free(str_path);
}

void	open_files_pipex(t_pipex *ppx, int argc, char *argv[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	ppx->fd_in = fd;
	if (fd == -1)
		perror(argv[1]);
	fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	ppx->fd_out = fd;
	return ;
}

t_pipex	*init_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*ppx;
	pid_t	*pids;

	ppx = (t_pipex *)malloc(sizeof(t_pipex));
	if (!ppx)
		return (NULL);
	ppx->argv = argv;
	ppx->envp = envp;
	ppx->argc = argc;
	ppx->paths = NULL;
	open_files_pipex(ppx, argc, argv);
	pids = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!pids)
	{
		free(ppx);
		return (NULL);
	}
	ppx->pids = pids;
	set_path_pipex(ppx, envp);
	return (ppx);
}

void	free_pipex(t_pipex *ppx)
{
	if (!ppx)
		return ;
	if (ppx->paths)
		ft_free_char2d(ppx->paths);
	if (ppx->pids)
		free(ppx->pids);
	free(ppx);
}
