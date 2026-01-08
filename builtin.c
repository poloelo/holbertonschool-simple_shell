#include "shell.h"

/**
 * shell_exit - Signal to exit the shell
 * @args: Array of arguments
 *
 * Return: -1 to signal exit to caller
 */
int shell_exit(char **args)
{
    (void)args;
    return (-1);  // NE PAS appeler exit() ici, juste retourner -1
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
    int status;
    char *builtins[] = {"exit", "env", NULL};
    int (*builtin_funcs[])(char **) = {shell_exit, shell_env};
    
    for (i = 0; builtins[i] != NULL; i++)
    {
        if (_strcmp(args[0], builtins[i]) == 0)
        {
            status = builtin_funcs[i](args);
            
            if (status == -1)  // shell_exit a retourné -1
                return (-1);    // Propager le signal au main
            
            return (0);  // Builtin exécuté avec succès
        }
    }
    
    return (1);  // Pas un builtin
}
