#include "shell.h"
#include <string.h> /* Include this header for strcmp */

/**
 * is_builtin - check if a command is a built-in
 * @cmd: double pointer to the command
 * Return: void
 */
void (*is_builtin(char **cmd))(char **)
{
	built_ins b[] = {
		{"exit", Exit},  /* Handle the exit command */
		{"env", _env},   /* Handle the env command */
		{"cd", _cd},     /* Handle the cd command */
		{NULL, NULL}
	};
	int i = 0;

	while (b[i].name != NULL)
	{
		if (strcmp(b[i].name, cmd[0]) == 0)
			return (b[i].f);
		i++;
	}
	return (NULL);
}

