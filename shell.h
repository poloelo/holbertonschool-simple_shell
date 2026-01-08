#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

extern int last_status;  /* Dernier code de sortie */
extern char **environ;

/* Main shell functions */
/* Main loop helpers */
int handle_empty_line(char *line);
int process_command(char *line, char **av, int line_count);
void display_prompt(void);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args, char *shell_name, int line_count);

/* Built-in functions */
int shell_exit(char **args);
int shell_env(char **args);
int check_builtin(char **args);

/* Path handling */
char *find_in_path(char *command);
char *get_path_env(void);

/* Helper functions */
void print_error(char *shell_name, int line_count, char *command);
void free_array(char **array);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strlen(char *s);

/* Command execution helpers */
char *get_command_path(char **args);
void execute_child(char *command, char **args, char *shell_name);

#endif /* SHELL_H */
