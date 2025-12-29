#include "shell.h"

void run_command(char *cmd, char *prog_name, int line)
{
	pid_t pid;
	char *args[] = {cmd, NULL};

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
