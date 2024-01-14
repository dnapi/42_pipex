#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "libft.h"

//can we use ernoo.h ??
//#include "errno.h"
# ifndef ENOENT
#  define ENOENT 2
# endif

# define READ_END 0;
# define WRITE_END 1;

typedef struct s_pipex
{
	char	***cmd;
	int		num_cmd;
	char	**paths;
	int		*pids;
	int		fd_in;
	int		fd_out;
	int		argc;
	char	**argv;
	char	**envp;
} t_pipex;

int is_path_defined(char *envp[]);
t_pipex *init_pipex(int argc, char *argv[], char *envp[]);

char  **get_args(char *commands);

#endif 
