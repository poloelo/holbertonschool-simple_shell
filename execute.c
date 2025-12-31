#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "shell.h"

/**
 * execute_command - execute a command
 * @line: command to execute
 * @env: environment variables
 *
 * Return: Nothing
 */
void execute_command(char *line, char **env)
{
	pid_t pid;
	char *argv[2];

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		argv[0] = line;
		argv[1] = NULL;

		if (execve(line, argv, env) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}
