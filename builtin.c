#include "shell.h"

/**
 * shell_exit - Exit the shell
 * @args: Array of arguments (unused)
 *
 * Return: Does not return
 */
int shell_exit(char **args)
{
    (void)args;
    exit(0);
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
 * Return: 0 if built-in was executed, 1 otherwise
 */
int check_builtin(char **args)
{
    if (_strcmp(args[0], "exit") == 0)
    {
        shell_exit(args);  // Ne retourne jamais
    }
    
    if (_strcmp(args[0], "env") == 0)
    {
        shell_env(args);
        return (0);
    }
    
    return (1);  // Pas un builtin
}
