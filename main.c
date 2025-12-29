#include "shell.h"

int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int line_count = 0;

	(void)argc;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;

		line_count++;
		line[nread - 1] = '\0';

		if (line[0] != '\0')
			run_command(line, argv[0], line_count);
	}

	free(line);
	return (0);
}
