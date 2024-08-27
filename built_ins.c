#include "shell.h"
/**
 * Exit - exit shell
 * @cmd: the "exit" command
 * Return: void
 */
void Exit(char **cmd)
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
/**
 * _cd - change current directory
 * @cmd: the "cd" command and its arguments
 * Return: Always 0
 */
void _cd(char **cmd)
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
	if (cdReturn == -1) /* cd fails! */
		dprintf(STDERR_FILENO, "can't cd to %s\n", dir);
	else
	{
		setenv("OLDPWD", cwd, 1);
		setenv("PWD", getcwd(dirBuff, sizeof(dirBuff)), 1);
	}
}
