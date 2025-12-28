#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void)
{
	char *line;
	size_t len;

	line = NULL;
	len = 0;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
		{
			printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		execute_command(line);
	}

	free(line);
	return (0);
}