#include "shell.h"
/**
 */
int main(void)
{
        char *directories = getenv("PATH");
        char pathCopy[PATH_MAX], *token, filepath[PATH_MAX];
	char file[] = "ls";

        if (directories == NULL)
                return (-1);
        strncpy(pathCopy, directories, sizeof(pathCopy));
	printf("PATH=%s\n", directories);
        printf("HTAP=%s\n", pathCopy);
	token = strtok(pathCopy, ":");
        while (token != NULL)
        {
                printf("%s\n", token);
		snprintf(filepath, sizeof(filepath), "%s/%s", token, file);
		printf("%s\n", filepath);
		if (access(filepath, F_OK | X_OK) != -1)
		{
			printf("YAY!   %s\n", filepath);
			return (0);
		}
                token = strtok(NULL, ":");
        }
	return (0);
}
