#include "shell.h"
/**
 * handle_comments - handle comments
 * (all strings following "#")
 * @input: the command line arguments
 * Return: void
 */
void handle_comments(char *input)
{
	int i, j;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			/* go back until we meet an empty space*/
			for (j = i; j >= 0; j--)
			{
				if (input[j] == ' ')
				{
					input[j] = '\0';
					break;
				}
			}
			break;
		}
	}
}
/**
 * handle_sigint - handle CTRL + C
 * @sigNum: signal number
 * Return: void
 */
void handle_sigint(int sigNum)
{
	if (sigNum == SIGINT)
		dprintf(STDOUT_FILENO, "\n$ ");
}
/**
 * handle_exit - exit the program
 * @input: pointer to command line arguments
 * @cmd: the "exit" command and/or its arguments
 * Return: void
 */
void handle_exit(char *input, char **cmd)
{
	int n = 0;

	if (strcmp(cmd[0], "exit") != 0)
		return;
	if (cmd[1])
	{
		n = atoi(cmd[1]);
		if (n == 0 && strcmp(cmd[1], "0") != 0)
		{
			dprintf(STDOUT_FILENO, "exit: %s: numeric argument required\n", cmd[1]);
			n = 1;
		}
	}
	free(input);
	exit(n);
}
