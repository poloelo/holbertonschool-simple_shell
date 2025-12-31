#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * parse_line - split a command line into arguments
 * @line: input string
 *
 * Return: array of strings (argv)
 */
char **parse_line(char *line)
{
	char **argv;
	char *token;
	int i;

	argv = malloc(sizeof(char *) * 64);
	if (argv == NULL)
		return (NULL);

	token = strtok(line, " ");
	i = 0;

	while (token != NULL)
	{
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}

	argv[i] = NULL;
	return (argv);
}
