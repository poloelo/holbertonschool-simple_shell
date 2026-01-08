#include "shell.h"

/**
 * process_line - Process a single line of input
 * @line: Line to process
 * @av: Argument vector
 * @line_count: Current line count
 *
 * Return: Status of execution
 */

int process_line(char *line, char **av, int line_count)
{
	char **args = NULL;
	int status = 0;

	if (line[0] == '\0' || line[0] == '\n')
	{
		free(line);
		return (0);
	}

	args = parse_line(line);
	free(line);

	if (args == NULL || args[0] == NULL)
	{
		free_array(args);
		return (0);
	}

	if (check_builtin(args) == 0)
	{
		free_array(args);
		return (0);
	}

	status = execute_command(args, av[0], line_count);
	free_array(args);

	last_status = status;  /* ← AJOUTE CETTE LIGNE */

	return (status);
}

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	char *line = NULL;
int last_status = 0;  /* Variable globale */
	int status = 0;
	int line_count = 0;
	(void)ac;

	while (1)
	{
		line_count++;

		if (isatty(STDIN_FILENO))
			display_prompt();

		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		status = process_line(line, av, line_count);
	}

	return (status);
}
