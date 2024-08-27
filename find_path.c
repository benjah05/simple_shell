#include "shell.h"
/**
 * cmd_exists - check if path exists and is executable
 * @path: path to file/command
 * Return: 1 on success, -1 on failure
 */
int cmd_exists(const char *path)
{
	if (access(path, F_OK | X_OK) == 0)
		return (1);
	return (-1);
}
/**
 * find_path - file command in PATH directories
 * @name: the name of the command (or path)
 * @filePath: buffer to hold the file's path
 * @pathLen: length of filePath buffer
 * Return: 1 on success, -1 on failure
 */
int find_path(char *name, char *filePath, size_t pathLen)
{
	char *directories = getenv("PATH"), *tokPtr = NULL;
	char *token, pathCopy[PATH_MAX];

	if (name[0] == '/')
	{
		if (cmd_exists(name) == 1)
		{
			snprintf(filePath, pathLen, "%s", name);
			return (1);
		}
		return (-1);
	}
	if (directories == NULL)
		return (-1);
	strncpy(pathCopy, directories, sizeof(pathCopy));
	pathCopy[sizeof(pathCopy) - 1] = '\0';
	token = strtok_r(pathCopy, ":", &tokPtr);
	while (token != NULL)
	{
		snprintf(filePath, pathLen, "%s/%s", token, name);
		if (cmd_exists(filePath) == 1)
			return (1);
		token = strtok_r(NULL, ":", &tokPtr);
	}
	return (-1);
}
