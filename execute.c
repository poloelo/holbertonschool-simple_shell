#include "shell.h"

/**
 * get_command_path - Get full path of command
 * @args: Array of arguments
 *
 * Return: Full path to command or NULL
 */
char *get_command_path(char **args)
{
	char *command = NULL;

	if (args[0][0] == '/' || args[0][0] == '.')
		command = args[0];
	else
		command = find_in_path(args[0]);

	return (command);
}

/**
 * execute_child - Execute command in child process
 * @command: Command path to execute
 * @args: Array of arguments
 * @shell_name: Name of the shell
 *
 * Return: Does not return (exits)
 */
void execute_child(char *command, char **args, char *shell_name)
{
	if (execve(command, args, environ) == -1)
	{
		perror(shell_name);
		if (command != args[0])
			free(command);
		exit(127);
	}
}

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

	command = get_command_path(args);

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
		execute_child(command, args, shell_name);
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
