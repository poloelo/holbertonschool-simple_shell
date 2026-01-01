#include "shell.h"

/**
 * display_prompt - Display shell prompt
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}

/**
 * read_line - Read a line from stdin
 *
 * Return: Pointer to the line read, or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	chars_read = getline(&line, &bufsize, stdin);

	if (chars_read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	return (line);
}

/**
 * parse_line - Parse input line into arguments
 * @line: Line to parse
 *
 * Return: Array of arguments
 */
char **parse_line(char *line)
{
	char **tokens = NULL;
	char *token = NULL;
	int i = 0;
	char *delim = " \t\r\n\a";

	tokens = malloc(sizeof(char *) * MAX_ARGS);
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delim);
	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = _strdup(token);
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;

	return (tokens);
}
