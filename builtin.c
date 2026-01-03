#include "shell.h"

/**
 * shell_exit - Exit the shell
 * @args: Array of arguments
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
 * @args: Array of arguments
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
 * check_builtin - Check if command is a built-in
 * @args: Array of arguments
 *
 * Return: 0 if built-in was executed, 1 otherwise
 */
int check_builtin(char **args)
{
	int i;
	char *builtins[] = {"exit", "env", NULL};
	int (*builtin_funcs[])(char **) = {shell_exit, shell_env};

	for (i = 0; builtins[i] != NULL; i++)
	{
		if (_strcmp(args[0], builtins[i]) == 0)
		{
			if (builtin_funcs[i](args) == -1)
				exit(EXIT_SUCCESS);
			return (0);
		}
	}

	return (1);
}
