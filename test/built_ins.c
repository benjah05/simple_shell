#include "shell.h"
/**
 * _exit - exit shell
 * @cmd: the "exit" command
 * Return: void
 */
void Exit(char **cmd)
{
	(void)cmd;
	exit(0);
}
/**
 * _env - current environment
 * @cmd: the "env" command
 * Return: void
 */
void _env(char **cmd)
{
	int i = 0;

	(void)cmd;
	for (i = 0; environ[i]; i++)
		dprintf(STDOUT_FILENO, "%s\n", environ[i]);
}
