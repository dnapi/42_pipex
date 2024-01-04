//#include "apue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int	main(int argc, char *argv[])
{
	printf("EACCES: %s\nENOENT=%d\n", strerror(EACCES),ENOENT);
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}
