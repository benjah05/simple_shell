#include "shell.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
 * resize_line_buffer - Resizes the line buffer if necessary
 * @linePtr: double pointer to the line buffer
 * @lineSize: current size of the line buffer
 * @totalLen: total length of data currently in the line buffer
 * Return: 0 on success, -1 on failure
 */
int resize_line_buffer(char **linePtr, size_t *lineSize, ssize_t totalLen)
{
	char *newLine;

	if (totalLen >= *lineSize)
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
	return (0);
}

/**
 * copy_to_line_buffer - Copies data from the buffer to the line buffer
 * @linePtr: double pointer to the line buffer
 * @totalLen: total length of data currently in the line buffer
 * @readBuff: buffer containing data to be copied
 * @buffIndex: current index in the buffer
 * @copyLen: number of bytes to copy
 */
void copy_to_line_buffer(char **linePtr, ssize_t *totalLen,
			 char *readBuff, size_t *buffIndex, size_t copyLen)
{
	memcpy(*linePtr + *totalLen, readBuff + *buffIndex, copyLen);
	*totalLen += copyLen;
	*buffIndex += copyLen;
}

/**
 * handle_newline - Handles the presence of a newline in the buffer
 * @newlinePos: position of the newline in the buffer
 * @buffIndex: current index in the buffer
 * @len: total length of data in the buffer
 * Return: number of bytes to copy
 */
size_t handle_newline(char *newlinePos, size_t *buffIndex, size_t len)
{
	return newlinePos ?
	       (size_t)(newlinePos - (*buffIndex + len) + 1) :
	       (len - *buffIndex);
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
	char *newlinePos = NULL;

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
		copyLen = handle_newline(newlinePos, &buffIndex, len);

		if (resize_line_buffer(linePtr, lineSize, totalLen + copyLen) == -1)
			return (-1);

		copy_to_line_buffer(linePtr, &totalLen, readBuff, &buffIndex, copyLen);

		if (newlinePos)
			break;
	}
	(*linePtr)[totalLen] = '\0';
	return (totalLen);
}
