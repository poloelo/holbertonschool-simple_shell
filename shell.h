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

extern char **environ;

/* Main shell functions */
void display_prompt(void);
char *read_line(void);
char **parse_line(char *line);
int execute_command(char **args, char *shell_name, int line_count);
int process_line(char *line, char **av, int line_count, int *last_status);

/* Built-in functions */
int shell_exit(char **args);
int shell_env(char **args);
int check_builtin(char **args);

/* Path handling */
char *find_in_path(char *command);
char *get_path_env(void);
char *get_command_path(char **args);

/* Helper functions */
void print_error(char *shell_name, int line_count, char *command);
void free_array(char **array);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
void execute_child(char *command, char **args, char *shell_name);

#endif /* SHELL_H */
