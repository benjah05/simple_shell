#include "shell.h"
/**
 * handle_comments - handle comments
 * (all strings following "#")
 * @input: the command line arguments
 * Return: void
 */
void handle_comments(char *input)
{
	int i;

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
			break;
	}
	input[i] = '\0';
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
