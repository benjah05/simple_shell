#include "shell.h"
/**
 * _setenv - set an environment variable
 * @cmd: the "setenv" command and its arguments
 * Return: void
 */
void _setenv(char **cmd)
{
	if (cmd[1] == NULL || cmd[2] == NULL)
	{
		dprintf(STDERR_FILENO, "Usage: setenv [variable] [value]\n");
		return;
	}
	if (setenv(cmd[1], cmd[2], 1) != 0)
		perror("setenv");
}
/**
 * _unsetenv - unset an environment variablle
 * @cmd: the "unsetenv" and its arguments
 * Return: void
 */
void _unsetenv(char **cmd)
{
	if (cmd[1] == NULL)
	{
		dprintf(STDERR_FILENO, "Usage: unsetenv [variable]\n");
		return;
	}
	if (unsetenv(cmd[1]) != 0)
		perror("unsetenv");
}
