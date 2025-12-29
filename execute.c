#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

int execute_command(char *cmd)
{
	pid_t pid;
	char *argv[2];

	pid = fork();
	if (pid == -1)
		return (-1);

	if (pid == 0)
	{
		argv[0] = cmd;
		argv[1] = NULL;
		execve(cmd, argv, NULL);
		perror("execve");
		exit(1);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}
