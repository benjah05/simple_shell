#include "shell.h"
/**
 * is_builtin - check if a command is a built-in
 * @cmd: double pointer to the command
 * Return: void
 */
void (*is_builtin(char **cmd))(char **)
{
	built_ins b[] = {
		{"exit", Exit},
		{"env", _env},
		{NULL, NULL}
	};
	int i = 0, j;

	while (b[i].name != NULL)
	{
		for (j = 0; cmd[j]; j++)
		{
			if (strcmp(b[i].name, cmd[j]) == 0)
				return (b[i].f);
		}
		i++;
	}
	return (NULL);
}
