#include "shell.h"
void run_cmd(char **cmd, char *agv);
void handle_input(char *agv, FILE *input_stream)
{
char *input = NULL, *command, *TokPtr = NULL;
size_t len = 0;
int readLine, i;
char *cmdV[ARG_MAX_VAL];
while (1)
{
if (isatty(fileno(stdin)) && input_stream == stdin)
dprintf(STDOUT_FILENO, "$ ");

readLine = getline(&input, &len, input_stream);
if (feof(input_stream))
break;

if (readLine == -1)
continue;

if (input[readLine - 1] == '\n')
input[readLine - 1] = '\0';

if (input == NULL || *input == '\n' || *input == '\t')
continue;
i = 0;
command = strtok_r(input, " \n", &TokPtr);
while (command != NULL && i < ARG_MAX_VAL - 1)
{
cmdV[i++] = command;
command = strtok_r(NULL, " \n", &TokPtr);
}
cmdV[i] = NULL;
if (cmdV[0] != NULL)
run_cmd(cmdV, agv);
}
free(input);
}
int main(int argc, char *argv[])
{
FILE *input_stream = stdin;
char cmd[100];

if (argc == 2)
{
snprintf(cmd, sizeof(cmd), "bash -c \"%s\"", argv[1]);
dprintf(STDOUT_FILENO, "%s\n", cmd);
fflush(stdout);
input_stream = popen(cmd, "r");
if (input_stream == NULL)
return (EXIT_FAILURE);
}
handle_input(argv[0], input_stream);
if (input_stream != stdin)
pclose(input_stream);
return (EXIT_SUCCESS);
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
extern char **environ;
void run_cmd(char **cmd, char *agv)
{
int path_found;
char **env = environ, path[PATH_MAX];
pid_t id;
if (strcmp(cmd[0], "setenv") == 0)
{
if (cmd[1] && cmd[2])
{
if (setenv(cmd[1], cmd[2], 1) != 0)
{
perror("setenv");
}
}
else
{
dprintf(STDERR_FILENO, "Usage: setenv VARIABLE VALUE\n");
}
return;
}
if (strcmp(cmd[0], "unsetenv") == 0)
{
if (cmd[1])
{
if (unsetenv(cmd[1]) != 0)
{
perror("unsetenv");
}
}
else
{
dprintf(STDERR_FILENO, "Usage: unsetenv VARIABLE\n");
}
return;
}
void (*f)(char **) = is_builtin(cmd);
if (f != NULL)
{
f(cmd);
return;
}
path_found = find_path(cmd[0], path, sizeof(path));
if (path_found != 1)
{
dprintf(STDERR_FILENO, "%s: No such file or directory\n", agv);
return;
}
cmd[0] = path;
id = fork();
if (id == 0)
{
if (execve(cmd[0], cmd, env) == -1)
{
dprintf(STDERR_FILENO, "%s: No such file or directory\n", agv);
_exit(EXIT_FAILURE);
}
}
else if (id > 0)
wait(NULL);
else
perror("fork");
}
