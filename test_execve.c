#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *programPath = "ls";
//    char *programPath = "/usr/bin/ls";
    char *args[] = { "ls", "-l", NULL }; // Command-line arguments for the program

    // Execute the program
    if (execve(programPath, args, NULL) == -1) {
        perror("execve"); // Print an error message if execve fails
        exit(EXIT_FAILURE);
    }

    // This part will only be reached if execve fails
    printf("This line will not be reached.\n");

    return 0;
}

