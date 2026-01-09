#include "shell.h"

/**
 * shell_exit - Signal to exit the shell
 * @args: Array of arguments (unused)
 *
 * Return: -1 to signal exit
 */
int shell_exit(char **args)
{
	(void)args;
	return (-1);
}

/**
 * shell_env - Print environment variables
 * @args: Array of arguments (unused)
 *
 * Return: 0 on success
 */
int shell_env(char **args)
{
	int i = 0;

	(void)args;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}

	return (0);
}

/**
 * check_builtin - Check if command is a built-in and execute it
 * @args: Array of arguments
 *
 * Return: -1 for exit, 0 if other builtin executed, 1 otherwise
 */
int check_builtin(char **args)
{
	if (_strcmp(args[0], "exit") == 0)
		return (shell_exit(args));

	if (_strcmp(args[0], "env") == 0)
	{
		shell_env(args);
		return (0);
	}

	return (1);
}
