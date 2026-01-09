#include "shell.h"

/**
 * get_path_env - Get PATH environment variable
 *
 * Return: Pointer to PATH string, or NULL
 */
char *get_path_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		if (environ[i][0] == 'P' && environ[i][1] == 'A' &&
		    environ[i][2] == 'T' && environ[i][3] == 'H' &&
		    environ[i][4] == '=')
		{
			return (environ[i] + 5);
		}
		i++;
	}

	return (NULL);
}

/**
 * find_in_path - Find command in PATH
 * @command: Command to find
 *
 * Return: Full path to command, or NULL if not found
 */
char *find_in_path(char *command)
{
	char *path_env, *path_copy, *token, *full_path;
	struct stat st;
	int cmd_len, dir_len;

	path_env = get_path_env();
	if (path_env == NULL)
		return (NULL);

	path_copy = _strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		dir_len = _strlen(token);
		cmd_len = _strlen(command);
		full_path = malloc(dir_len + cmd_len + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		full_path[0] = '\0';
		_strcat(full_path, token);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (stat(full_path, &st) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
