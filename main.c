#include "shell.h"

/**
 * handle_empty_line - Handle empty line input
 * @line: Line to check
 *
 * Return: 1 if line is empty, 0 otherwise
 */
int handle_empty_line(char *line)
{
	if (line[0] == '\0' || line[0] == '\n')
	{
		free(line);
		return (1);
	}
	return (0);
}

/**
 * process_command - Process and execute a command
 * @line: Line to process
 * @av: Argument vector
 * @line_count: Current line count
 *
 * Return: Status of execution
 */
int process_command(char *line, char **av, int line_count)
{
	char **args = NULL;
	int status = 0;

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

		if (handle_empty_line(line))
			continue;

		status = process_command(line, av, line_count);
	}

	return (status);
}
