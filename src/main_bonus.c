/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:11:33 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/17 13:44:18 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_outfile(char *str)
{
	write(2, "zsh: permission denied: ", 24);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*ppx;
	int		status;

	if (argc < 5)
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
	if (ppx->fd_out == -1)
		error_outfile(argv[argc - 1]);
	free_pipex(ppx);
	return (status);
}
