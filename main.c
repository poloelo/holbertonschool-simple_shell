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

        status = check_builtin(args);
        
        if (status == -1)  // exit a été appelé
        {
            free_array(args);
            exit(EXIT_SUCCESS);  // Quitter proprement
        }
        
        if (status == 0)  // Builtin exécuté
        {
            free_array(args);
            continue;
        }

        // status == 1, pas un builtin → exécuter la commande
        status = execute_command(args, av[0], line_count);
        free_array(args);
    }

    return (status);
}
