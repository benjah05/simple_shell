#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * _setenv - sets an environment variable
 * @args: array of arguments (args[0] = "setenv", args[1] = variable,
 * args[2] = value)
 * Description: This function sets the environment variable specified by
 * args[1] to the value specified by args[2]. If the variable already exists,
 * it updates its value. If the number of arguments is incorrect or if setting
 * the environment variable fails, an error message is printed.
 * Return: void
 */
void _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	if (setenv(args[1], args[2], 1) != 0)
	{
		perror("setenv");
	}
}

/**
 * _unsetenv - unsets an environment variable
 * @args: array of arguments (args[0] = "unsetenv", args[1] = variable)
 * Description: This function unsets the environment variable specified by
 * args[1]. If the number of arguments is incorrect or if unsetting the
 * environment variable fails, an error message is printed.
 * Return: void
 */
void _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}

	if (unsetenv(args[1]) != 0)
	{
		perror("unsetenv");
	}
}

/**
 * Exit - exits the shell
 * @args: array of arguments (args[0] = "exit", args[1] = optional
 * exit status)
 * Description: This function exits the shell with the status provided in
 * args[1] or with status 0 if no status is provided. If args[1] is not a valid
 * integer, it prints an error message and exits with status 1.
 * Return: void
 */
void Exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
		if (status == 0 && strcmp(args[1], "0") != 0)
		{
			fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
			status = 1;
		}
	}

	exit(status);
}

/**
 * _env - prints the environment variables
 * @args: array of arguments (args[0] = "env")
 * Description: This function prints the current environment variables to
 * the standard output.
 * Return: void
 */
void _env(char **args)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * _cd - changes the current working directory
 * @args: array of arguments (args[0] = "cd", args[1] = new directory)
 * Description: This function changes the current working directory to the
 * directory specified by args[1]. If no directory is specified, it changes to
 * the home directory. If changing the directory fails, an error message is
 * printed.
 * Return: void
 */
void _cd(char **args)
{
	if (args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
		}
	}
}

