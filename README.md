# Simple Shell

A simple UNIX command line interpreter written in C.

## Description

This project is a simple implementation of a shell, a command-line interpreter that provides a user interface for the UNIX operating system. The shell reads commands from the user and executes them.

[Flowchart.pdf](https://github.com/user-attachments/files/24496211/Flowchart.pdf)

## Features

- Display a prompt and wait for user input
- Execute commands with full path (e.g., `/bin/ls`)
- Execute commands using PATH
- Handle command-line arguments
- Implement built-in commands: `exit` and `env`
- Handle the end-of-file condition (Ctrl+D)
- Handle errors with appropriate error messages
- Work in both interactive and non-interactive mode

## Compilation

Compile all `.c` files together:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
$ /bin/ls
hsh main.c shell.c
$ ls -l
total 100
-rwxrwxr-x 1 user user 18192 Dec  5 10:00 hsh
-rw-rw-r-- 1 user user  1540 Dec  5 09:58 main.c
$ exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$ cat test_commands
/bin/ls
pwd
$ cat test_commands | ./hsh
hsh main.c shell.c
/home/user/simple_shell
```

## Built-in Commands

- `exit`: Exit the shell
- `env`: Print the current environment variables

## Files

- `shell.h`: Header file containing function prototypes and includes
- `main.c`: Main entry point of the shell
- `prompt.c`: Functions for displaying prompt and reading input
- `execute.c`: Functions for executing commands
- `builtin.c`: Built-in command implementations
- `path.c`: PATH handling functions
- `helpers.c`: Helper functions for error handling and memory management
- `string_utils.c`: String manipulation utility functions
- `AUTHORS`: List of contributors to the project
- `README.md`: Project documentation
- `man_1_simple_shell`: Manual page for the simple shell

## Requirements

- Ubuntu 20.04 LTS
- gcc compiler with flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Betty style compliant code

## Authors

See the AUTHORS file for a list of contributors to this project.

## Acknowledgments

This project is part of the Holberton School curriculum.

