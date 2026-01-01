#include "shell.h"

/**
 * execute_command - Execute a command
 * @args: Array of arguments
 * @shell_name: Name of the shell (argv[0])
 * @line_count: Current line number
 *
 * Return: Status of execution
 */
int execute_command(char **args, char *shell_name, int line_count)
{
	pid_t pid;
	int status;
	char *command = NULL;
	struct stat st;

	if (args[0][0] == '/' || args[0][0] == '.')
		command = args[0];
	else
		command = find_in_path(args[0]);

	if (command == NULL || stat(command, &st) != 0)
	{
		print_error(shell_name, line_count, args[0]);
		if (command != NULL && command != args[0])
			free(command);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (command != args[0])
			free(command);
		return (1);
	}

	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
		{
			perror(shell_name);
			if (command != args[0])
				free(command);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (command != args[0])
			free(command);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}

	return (0);
}

