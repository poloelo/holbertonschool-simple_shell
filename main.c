#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Description: This function initializes and runs a simple shell program
 * that reads commands from the user and executes them.
 *
 * Return: Always 0 (Success)
 */
int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);

	(void)ac;
	(void)av;

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (_strlen(line) > 0)
			execute_command(line, env);
	}

	free(line);
	return (0);
}
