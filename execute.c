#include "shell.h"

/**
 * get_command_path - Get full path of a command
 * @args: Array of arguments
 *
 * Return: Full path of the command or NULL if not found
 */
char *get_command_path(char **args)
{
	char *command = NULL;

	if (args[0][0] == '/' || args[0][0] == '.')
		command = _strdup(args[0]);
	else
		command = find_in_path(args[0]);

	return (command);
}

/**
 * execute_child - Execute a command in child process
 * @command: Full path to command
 * @args: Array of arguments
 * @shell_name: Name of the shell for error messages
 */
void execute_child(char *command, char **args, char *shell_name)
{
	if (access(command, X_OK) != 0)
	{
		write(STDERR_FILENO, shell_name, _strlen(shell_name));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		exit(126);
	}

	if (execve(command, args, environ) == -1)
	{
		perror(shell_name);
		exit(127);
	}
}

/**
 * execute_command - Execute a command (builtin or external)
 * @args: Array of arguments
 * @shell_name: Name of the shell (argv[0])
 * @line_count: Current line number for error messages
 *
 * Return: Status code of the executed command
 */
int execute_command(char **args, char *shell_name, int line_count)
{
	pid_t pid;
	int status;
	char *command = NULL;
	struct stat st;

	if (args[0] == NULL)
		return (0);

	command = get_command_path(args);
	if (command == NULL || stat(command, &st) != 0)
	{
		print_error(shell_name, line_count, args[0]);
		if (command != NULL)
			free(command);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(command);
		return (1);
	}

	if (pid == 0)
	{
		execute_child(command, args, shell_name);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (command != NULL)
			free(command);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (0);
}
