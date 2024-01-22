# Project Description: Pipex

In the `pipex` project of 42 School @ [Hive Helsinki](https://www.hive.fi/en/),  I have created simplified version of the shell's pipe functionality in C  programming language. The goal is to implement a program that can execute two or more commands provided as arguments, simulating the behavior of the shell when using the `|` operator. List ofof allowed function include : open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid.

## Key Tasks and Features

1. **Argument Parsing:**
   - The program should parse command-line arguments, including the two commands to be executed.
   
2. **Process Creation:**
   - Create two (or more) child processes to execute each command.
   - Use the `pipe()` system call to establish communication between the two processes.
   - The parent process should wait for the child processes to complete.

3. **Redirection:**
   - Redirect the standard output of the first process to the write end of the pipe.
   - Redirect the standard input of the second process to the read end of the pipe.

4. **Execution and Error Handling:**
   - Execute the commands in the created processes using `execve()`.
   - Implement robust error handling throughout the program to deal with potential issues in command execution or other stages.

The goal is to gain a better understanding of process creation, interprocess communication using pipes, and basic system calls. We consider edge cases and ensure their implementation is robust and handles various scenarios.

## Pipex Program Usage

The `pipex` program to replicate the behavior of shell pipelinesi
```bash
./pipex file1 cmd1 cmd2 cmd3 file2
```
For example:
```bash
./pipex input.txt "grep hello" "wc -l" "cat" output.txt
```

Our implementation handels, so multiple pipes:
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Should behave like:
```bash
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```
