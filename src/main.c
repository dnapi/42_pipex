/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:36:25 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/16 18:08:49 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*ppx;
	int		status;

	if (argc != 5)
	{
		write(2, "Error: wrong number of arguments.\n", 35);
		return (1);
	}
	status = 0;
	ppx = init_pipex(argc, argv, envp);
	if (!ppx)
		return (1);
	dup2(ppx->fd_in, STDIN_FILENO);
	close(ppx->fd_in);
	status = pipex(ppx);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (ppx->paths)
		ft_free_char2d(ppx->paths);
	return (status);
}

void	ft_free_char2d(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
