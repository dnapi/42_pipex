env -i   -> segm fault
./pipex  nonexisting  noexisting nonexisting  file

a) fd leaks
	You can add the line while (1); right before your program ends. 
	lsof -c pipex

b) memory leaks
	flag      -fsanitize=address


Advanced Programming in the Unix Environment, Richard Stevens
codes http://www.apuebook.com/code3e.html

The Linux Programmer's Guide, Sven Goldt et al.
https://tldp.org/LDP/lpg/lpg.html

https://csnotes.medium.com/pipex-tutorial-42-project-4469f5dd5901
https://medium.com/@lannur-s/pipex-42-chapter-1-metamorphosis-execve-1a4710ab8cb1
https://reactive.so/post/42-a-comprehensive-guide-to-pipex
https://dev.to/herbievine/42-a-comprehensive-guide-to-pipex-5165

https://github.com/madebypixel02/pipex
https://stackoverflow.com/questions/8389033/implementation-of-multiple-pipes-in-c


open: <fcntl.h>
close: <unistd.h>
read: <unistd.h>
write: <unistd.h>

malloc: <stdlib.h>
free: <stdlib.h>

perror: <stdio.h>
strerror: <string.h>

access: <unistd.h>
dup: <unistd.h>
dup2: <unistd.h>
execve: <unistd.h>
fork: <unistd.h>
pipe: <unistd.h>
wait: <sys/wait.h> or <unistd.h>
waitpid: <sys/wait.h> or <unistd.h>
unlink: <unistd.h>
exit: <stdlib.h>
