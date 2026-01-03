#include "shell.h"

/**
 * print_error - Print error message
 * @shell_name: Name of the shell
 * @line_count: Line number
 * @command: Command that failed
 */
void print_error(char *shell_name, int line_count, char *command)
{
	int num, temp, divisor = 1;

	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);

	/* Convert line_count to string */
	temp = line_count;
	while (temp / 10 != 0)
	{
		divisor *= 10;
		temp /= 10;
	}

	while (divisor > 0)
	{
		num = (line_count / divisor) % 10;
		write(STDERR_FILENO, &"0123456789"[num], 1);
		divisor /= 10;
	}

	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * free_array - Free array of strings
 * @array: Array to free
 */
void free_array(char **array)
{
	int i = 0;

	if (array == NULL)
		return;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}

	free(array);
}
