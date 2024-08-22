#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

extern char **environ;
#define ARG_MAX_VAL 1024

void handle_input(char *arg, FILE *input_stream);
void run_cmd(char **cd, char *arg);
int cmd_exists(const char *pathname);
int find_path(char *n, char *pathBuffer, size_t buffSize);
void (*is_builtin(char **cd))(char **cd);
void Exit(char **cmd);
void _env(char **cmd);
/**
 * struct builtin_functions - struct that holds built-in functions' names
 * and their custom defined functions
 * @name: the name of the built-in
 * @f: the custom function
 */
typedef struct builtin_functions
{
	char *name;
	void (*f)(char **);
} built_ins;

#endif
