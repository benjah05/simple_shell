#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;
void handle_input(char *arg);
void run_cmd(char *cd, char *arg);
int cmd_exists(const char *pathname);
int find_path(char *n, char *pathBuffer, size_t buffSize);

#endif
