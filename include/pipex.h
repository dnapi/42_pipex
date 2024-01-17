/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apimikov <apimikov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 11:06:26 by apimikov          #+#    #+#             */
/*   Updated: 2024/01/17 11:06:47 by apimikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "libft.h"

typedef struct s_pipex
{
	char	**paths;
	int		*pids;
	int		fd_in;
	int		fd_out;
	int		argc;
	char	**argv;
	char	**envp;
}	t_pipex;

int		is_path_defined(char *envp[]);
t_pipex	*init_pipex(int argc, char *argv[], char *envp[]);
void	free_pipex(t_pipex *ppx);
void	ft_free_char2d(char **split);
int		pipex(t_pipex *ppx);

#endif
