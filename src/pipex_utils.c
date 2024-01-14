/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 06:33:46 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/12 13:16:19 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "pipex.h"
#include "../include/pipex.h"

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

void set_path_pipex(t_pipex *pnt, char *envp[])
{
	int	pos;
	char	*str_path;
	
	pos = -1;
	if (envp)
		pos = is_path_defined(envp);
	if (pos > -1)
	{
		str_path = ft_strjoin(envp[pos], \
			   	":/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	}
	else
		str_path = ft_strdup(":/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	pnt->paths = ft_split(str_path + 5, ':');
	free(str_path);
}


void	open_files_pipex(t_pipex *ppx, int argc, char *argv[])
{
	int fd;

	fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
//    ft_printf("er num=%d\n", ENOENT);
//      strerror(ENOENT);
        perror(argv[1]);
    }
	ppx->fd_in = fd;

	fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
        perror(argv[argc - 1]);
	ppx->fd_out = fd;

	return ;
}

t_pipex	*init_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*ppx;

	(void)argv;
	
	ppx = (t_pipex *)malloc(sizeof(t_pipex));
	if (!ppx)
		return (NULL);
	set_path_pipex(ppx, envp);
	ppx->num_cmd = argc - 3;
	ppx->argv = argv;
	ppx->envp = envp;
	ppx->argc = argc;
	open_files_pipex(ppx, argc, argv);

	return (ppx);
}
