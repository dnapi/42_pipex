//#include "pipex.h"
#include  "../include/pipex.h"


/*
char	**this_is_awkward(char *commands)
{
	char	**awk_args;
	char	**args;

	awk_args = (char **)malloc(sizeof(char *) * 3);
	args = ft_split(commands, '\'');
	if (awk_args && args && args[0] && args[1])
	{
		awk_args[2] = NULL;
		awk_args[0] = ft_strtrim(args[0], " ");
		awk_args[1] = ft_strdup(args[1]);
	}
//	free_array(args);
	return (awk_args);
}

char	**get_args(char *commands)
{
	char	**args;

//	if (commands[0] == '\0')
//		return (NULL);
	if (ft_strchr(commands, '\''))
		args = this_is_awkward(commands);
	else
		args = ft_split(commands, ' ');
	return (args);
}
*/

void	ft_free_char2d(char **split)
{
	size_t	i;

	i = 0;
	//remove unused function above
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}


