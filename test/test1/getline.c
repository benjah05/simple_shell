#include "shell.h"
/**
 * read_input - read input into input
 * @readBuff: buffer used to read data
 * @len: total length of data read into the line (input)
 * @input_stream: the stream from which data is coming from
 * Return: number of characters read into input
 */
ssize_t read_input(char *readBuff, size_t *len, FILE *input_stream)
{
	ssize_t readLen;

	if (*len > 0)
		return (*len);
	readLen = fread(readBuff, 1, *len, input_stream);
	if (readLen > 0)
		*len = readLen;
	else
		*len = 0;
	return (readLen);
}
/**
 * _getline - custom getline function
 * @linePtr: double pointer to the where the input is read
 * @lineSize: the size of input (line)
 * @input_stream: stream from which data is coming from
 * Return: number of characters read into linePtr
 */
ssize_t _getline(char **linePtr, size_t *lineSize, FILE *input_stream)
{
	static char readBuff[READ_BUFFER_SIZE];
	size_t len = 0, buffIndex = 0, copyLen = 0;
	ssize_t bytesRead = 0, totalLen = 0;
	char *newLine = NULL, *newlinePos = NULL;

	if (*linePtr == NULL || *lineSize == 0)
	{
		*lineSize = READ_BUFFER_SIZE;
		*linePtr = malloc(*lineSize);
		if (*linePtr == NULL)
			return (-1);
	}
	while (1)
	{
		if (buffIndex == len)
		{
			bytesRead = read_input(readBuff, &len, input_stream);
			if (bytesRead < 0)
			{
				free(*linePtr);
				return (-1);
			}
			if (bytesRead == 0)
				break; /* EOF */
			buffIndex = 0; /* reset buffer index */
		}
		newlinePos = memchr(readBuff + buffIndex, '\n', len - buffIndex);
		/*copyLen = newlinePos ? ((size_t)newlinePos - (readBuff + buffIndex) + 1) : (len - buffIndex);*/
		if (totalLen + copyLen >= *lineSize)
		{
			*lineSize += READ_BUFFER_SIZE;
			newLine = realloc(*linePtr, *lineSize);
			if (newLine == NULL)
			{
				free(*linePtr);
				return (-1);
			}
			*linePtr = newLine;
		}
		memcpy(*linePtr + totalLen, readBuff + buffIndex, copyLen);
		totalLen += copyLen;
		buffIndex += copyLen;
		if (newlinePos)
			break;
	}
	*linePtr[totalLen] = '\0';
	return (totalLen);
}
