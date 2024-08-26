#include "shell.h"
#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
:
/*
 *
 *  _setenv - Sets an environment variable
 * @name: The name of the variable to set
 * @value: The value to set the variable to
 * * Description: This function sets an environment variable
 * in the environment of the calling process.
 *
 * Return: 0 on success, -1 on failure
 * /
int _setenv(const char *name, const char *value);
/*
 *
 * _unsetenv - Unsets an environment variable
 * @name: The name of the variable to unset
 *
 * Description: This function unsets an environment variable
 * in the environment of the calling process.
 *
 * Return: 0 on success, -1 on failure
 * /
int _unsetenv(const char *name);
/*
 *
 *  Exit - Exits the shell program
 *  @status: The exit status to use
 *
 *  Description: This function exits the shell program
 * with the specified status.
 * /
void Exit(int status);

/*
 *
 * _env - Prints the environment variables
 *
 * Description: This function prints all environment variables
 * of the current process.
 * /
void _env(void);

/*
 *
 *  _cd - Changes the current directory
 *  @path: The path to change to
 *
 *  Description: This function changes the current working directory
 *  to the specified path.
 *
 *  Return: 0 on success, -1 on failure
 * /
int _cd(const char *path);
void _setenv(char * * cmd)
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
dprintf(STDERR_FILENO, "Usage: setenv VAR VALUE\n");
}
}

/ * *
 *     _unsetenv - remove an environment variable
 *     @cmd: the "unsetenv" command and its arguments
 *     Return: void
 *    /
void _unsetenv(char * * cmd)
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
dprintf(STDERR_FILENO, "Usage: unsetenv VAR\n");
}
}

/ * *
 *     Exit - exit shell
 *     @cmd: the "exit" command
 *     Return: void
 *    /
void Exit(char * * cmd)
{
int n = 0;

if (cmd[1])
{
n = atoi(cmd[1]);
if (!n)
{
dprintf(STDERR_FILENO, "numeric argument required\n");
return;
}
}
exit(n);
}
/ * *
 *     _env - current environment
 *     @cmd: the "env" command
 *     Return: void
 *    /
void _env(char * * cmd)
{
int i = 0;

(void)cmd;
for (i = 0; environ[i]; i++)
dprintf(STDOUT_FILENO, "%s\n", environ[i]);
}
/ * *
 *     _cd - change current directory
 *     @cmd: the "cd" command and its arguments
 *     Return: Always 0
 *    /
void _cd(char * * cmd)
{
char *cwd, *dir, dirBuff[1024];
int cdReturn;

cwd = getcwd(dirBuff, sizeof(dirBuff));
if (cwd == NULL)
perror("getcwd");
if (!cmd[1])
{
dir = getenv("HOME");
if (dir == NULL)
dir = getenv("PWD");
}
else if (strcmp(cmd[1], "-") == 0)
{
dir = getenv("OLDPWD");
if (dir == NULL)
dprintf(STDOUT_FILENO, "%s\n", cwd);
else
dprintf(STDOUT_FILENO, "%s\n", dir);
}
else
{
if (cmd[1][0] == '$')
{
dir = getenv(cmd[1] + 1);
if (dir == NULL)
dprintf(STDOUT_FILENO, "\n");
}
else
dir = cmd[1];
}
cdReturn = chdir(dir);
if (cdReturn == -1) / * *  cd fails!
 *   /
dprintf(STDERR_FILENO, "can't cd to %s\n", dir);
else
{
setenv("OLDPWD", cwd, 1);
setenv("PWD", getcwd(dirBuff, sizeof(dirBuff)), 1);
}
}
