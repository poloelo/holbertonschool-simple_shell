#include "shell.h"

void run_command(char *cmd, char *prog_name, int line)
{
	pid_t pid;
	char *args[2];

	args[0] = cmd;
	args[1] = NULL;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line, cmd);
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}
