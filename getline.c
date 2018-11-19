#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h> /* used for invalid argument */

/**
 * *_realloc - reallocates memory block and copies old->new
 *
 * @ptr: points to old memory
 *
 * @old_size: size in bytes of old memory
 *
 * @new_size: size in bytes of new memory
 *
 * Return: pointer to new memory @new
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new;
	char *temp;
	unsigned int i;

	if (ptr == NULL)
	{
		ptr = malloc(new_size);

		if (ptr == NULL)
			return (NULL);

		return (ptr);
	}

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);

	if (new == NULL)
		return (NULL);

	old_size = (new_size < old_size) ? new_size : old_size;

	temp = ptr;

	for (i = 0; i < old_size; i++)
	{
		*(new + i) = *(temp + i);
	}
	free(ptr);

	return (new);
}

/**
 * _fgetc - Gets next character in stream
 * and advances pointer forward in input stream
 *
 * @fp: Pointer to input stream
 *
 * Return: unsigned char -> int (success)
 *         EOF (failure)
 */

int _fgetc(FILE *fp)
{
	int is_read;
	unsigned char c;

	if (fp->ungetcflag) /* char is EOF */
	{
		fp->ungetcflag = 0; /* clears EOF flag */
		return (fp->ungetchar); /* sets to index before ungetc call */
	}

	is_read = read (fp->fd, &c, 1); /* reads 1 char a.a.t. */
	if (is_read <= 0)
		return (EOF);

	return (c);
}

/**
 * _getline - Reads entire line from stream
 *
 * @line: Pointer to pointer to line to get
 *
 * @n: number of characters to read
 *
 * @stream: input source
 *
 * Return: No of chars read (success)
 *         -1 (failure)
 */

ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	int input, max = 128;
	size_t i, new_size;
	char *new_buffer = NULL;

	if (!lineptr || !n || !stream)
	{
		errno = EINVAL; /* invalid arguments */
		return (-1);
	}

	input = _fgetc(stream)
	if (input == EOF)
		return (-1);

	if (!*line)
	{
		*line = malloc(max);
		if (!*line)
		{
			free(line);
			return (-1);
		}
	}
	*n = max;

	i = 0;
	while (input != EOF)
	{
		if (i + 1 >= *n) /* input > max */
		{
			new_size = *n + (*n >> 2) /* add 32 bits */
			if (new_size < max)
				new_size = max;
		}
		new_buffer = _realloc(*line, new_size); /* enlarge/cp buffer */
		if (!new_buffer)
			return (-1); /* MIGHT NEED A FREE? */
		*n = new_size;
		*line = new_buffer;
		((unsigned char *)(*line))[i++] = c;
		if (input == '\n')
			break;
		input = _fgetc(stream);
	}
	(*line)[i] = '\0';
	return (i);
}
