#include "shell.h"
void run_cmd(char **cd, char *arg);
/**
* handle_input - take input from stdin
* @agv: command line argument(executable file)
* @input_stream: stdin or file
* Return: void
*/
void handle_input(char *agv, FILE *input_stream)
{
	char *input = NULL, *command, *TokPtr = NULL;
	size_t len = 0;
	int readLine, i;
	char *cmdV[ARG_MAX_VAL];

	while (1)
	{
		if (isatty(fileno(stdin)) && input_stream == stdin)
			dprintf(STDOUT_FILENO, "$ ");
		readLine = getline(&input, &len, input_stream);
		if (feof(input_stream))
			break;
		if (readLine == -1)
			continue;
		if (input[readLine - 1] == '\n')
			input[readLine - 1] = '\0';
		if (input == NULL || *input == '\n' || *input == '\t')
			continue;
		handle_comments(input);
		i = 0;
		command = strtok_r(input, " \n", &TokPtr);
		while (command != NULL && i < ARG_MAX_VAL - 1)
		{
			cmdV[i++] = command;
			command = strtok_r(NULL, " \n", &TokPtr);
		}
		cmdV[i] = NULL;
		if (cmdV[0] != NULL)
			run_cmd(cmdV, agv);
	}
	free(input);
}
/**
* run_cmd - run commands
* @cmd: double pointer to the command line args
* @agv: cl argument(compiled file)
* Return: void
*/
void run_cmd(char **cmd, char *agv)
{
	int path_found;
	char **env = environ, path[PATH_MAX];
	pid_t id;
	void (*f)(char **) = is_builtin(cmd);

	if (f != NULL)
	{
		f(cmd);
		return;
	}
	path_found = find_path(cmd[0], path, sizeof(path));
	if (path_found != 1)
	{
		dprintf(STDERR_FILENO, "%s: No such file or directory\n", agv);
		return;
	}
	cmd[0] = path;
	id = fork();
	if (id == 0)
	{
		if (execve(cmd[0], cmd, env) == -1)
		{
			dprintf(STDERR_FILENO, "%s: No such file or directory\n", agv);
			_exit(EXIT_FAILURE);
		}
	}
	else if (id > 0)
		wait(NULL);
	else
		perror("fork");
}
/**
* main - simple shell
* @argc: argument count
* @argv: argument vector
* Return: 0
*/
int main(int argc, char *argv[])
{
	FILE *input_stream = stdin;
	char cmd[100];

	if (argc == 2)
	{
		snprintf(cmd, sizeof(cmd), "bash -c \"%s\"", argv[1]);
		dprintf(STDOUT_FILENO, "%s\n", cmd);
		fflush(stdout);
		input_stream = popen(cmd, O_RDONLY);
		if (input_stream == NULL)
			return (EXIT_FAILURE);
	}
	/* signal(SIGINT, handle_sigint); */
	handle_input(argv[0], input_stream);
	if (input_stream != stdin)
		pclose(input_stream);
	return (EXIT_SUCCESS);
}
