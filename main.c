#include "shell.h"

/**
 * process_line - Process a single line of input
 * @line: Line to process
 * @av: Argument vector
 * @line_count: Current line count
 * @last_status: Pointer to last command status
 *
 * Return: Status of execution, -1 for exit signal
 */
int process_line(char *line, char **av, int line_count, int *last_status)
{
	char **args = NULL;
	int status = 0;

	if (line[0] == '\0' || line[0] == '\n')
	{
		free(line);
		return (*last_status);
	}

	args = parse_line(line);
	free(line);

	if (args == NULL || args[0] == NULL)
	{
		free_array(args);
		return (*last_status);
	}

	status = check_builtin(args);

	if (status == -1)
	{
		free_array(args);
		return (-1);
	}

	if (status == 0)
	{
		free_array(args);
		return (*last_status);
	}

	status = execute_command(args, av[0], line_count);
	free_array(args);
	*last_status = status;

	return (status);
}

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: Last command status
 */
int main(int ac, char **av)
{
	char *line = NULL;
	int status = 0;
	int line_count = 0;
	int last_status = 0;
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

		status = process_line(line, av, line_count, &last_status);

		if (status == -1)
			break;
	}

	return (last_status);
}
