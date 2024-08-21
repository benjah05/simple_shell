#include "shell.h"
void run_cmd(char *cd, char *arg);
/**
 * handle_input - take input from stdin
 * @agv: command line argument(executable file)
 * Return: void
 */
void handle_input(char *agv)
{
	char *input = NULL, *command;
	size_t len = 0;
	int readLine;

	while (1)
	{
		if (isatty(fileno(stdin)))
			dprintf(STDOUT_FILENO, "$ ");
		readLine = getline(&input, &len, stdin);
		if (feof(stdin))
			break;
		if (readLine == -1)
			continue;
		if (input[readLine - 1] == '\n')
			input[readLine - 1] = '\0';
		command = strtok(input, " \n");
		while (command != NULL)
		{
			run_cmd(command, agv);
			command = strtok(NULL, " \n");
		}
	}
	free(input);
}
/**
 * run_cmd - run commands
 * @cmd: the command
 * @agv: cl argument(executable file)
 * Return: void
 */
void run_cmd(char *cmd, char *agv)
{
	int all_spaces, i = 0, path_found;
	char *cmdV[2], **env = environ, path[PATH_MAX];
	pid_t id = -1;

	all_spaces = 1;
	for (i = 0; cmd[i]; i++)
	{
		if (!isspace(cmd[i]))
		{
			all_spaces = 0;
			break;
		}
	}
	if (all_spaces)
		return;
	path_found = find_path(cmd, path, sizeof(path));
	if (path_found != 1 && id == -1)
	{
		dprintf(STDERR_FILENO, "%s: No such file or directory\n", agv);
		return;
	}
	cmdV[0] = path;
	cmdV[1] = NULL;
	id = fork();
	if (id == -1)
	{
		perror("fork");
		return;
	}
	if (id == 0)
	{
		if (execve(cmdV[0], cmdV, env) == -1)
		{
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", agv);
			_exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}
/**
 * main - simple shell
 * @argc: argument count
 * @argv: argument vector
 * Return: 0
 */
int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		dprintf(STDERR_FILENO, "Usage: %s\n", argv[0]);
		return (-1);
	}
	handle_input(argv[0]);
	return (0);
}
