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

typedef struct s_str
{
	int cmd;
	int	*pids;
	int last_in;
} t_str;


#endif 
