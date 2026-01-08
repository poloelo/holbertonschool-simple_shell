#include "shell.h"

/**
 * main - Entry point for simple shell
 * @ac: Argument count
 * @av: Argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
    char *line = NULL;
    char **args = NULL;
    int status = 0;
    int line_count = 0;
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

        if (line[0] == '\0' || line[0] == '\n')
        {
            free(line);
            continue;
        }

        args = parse_line(line);
        free(line);

        if (args == NULL || args[0] == NULL)
        {
            free_array(args);
            continue;
        }

        if (check_builtin(args) == 0)
        {
            free_array(args);
            continue;
        }

        status = execute_command(args, av[0], line_count);
        free_array(args);
    }

    return (status);
}
