#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

extern char **environ;

/**
 * run_command - read and execute commands
 *
 * Return: Nothing
 */
void run_command(void)
{
	char *line;
	size_t len;

	line = NULL;
	len = 0;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);

		if (getline(&line, &len, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		line[strcspn(line, "\n")] = '\0';

		if (line[0] == '\0')
			continue;

		execute_command(line, environ);
	}

	free(line);
}
