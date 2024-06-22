/*
 * File_name: error.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _eputs - Whispers the string softly to the console.
 *
 * @_eputs takes a gentle string @str, and with grace,
 * it murmurs it to the console, sharing its secrets
 * quietly. No return, only the gentlest of echoes.
 *
 * @str: The string to be whispered.
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - Casts your character onto the stage of stderr.
 *
 * @c: The character to take center stage.
 *
 * Return: The applause of 1 on success.
 * On a tragic error, the curtains fall with -1, and errno sets the mood.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - Emits a character to a specified file descriptor.
 *
 * This function writes the provided character 'c' to the specified
 * file descriptor 'fd', allowing for tailored output streams.
 *
 * @c: The character to be sent to the file descriptor.
 * @fd: The target file descriptor for the character output.
 *
 * Return: Returns 1 on success. On failure, it returns -1 and sets
 *         the errno variable to indicate the error.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Print a string to a specified file descriptor.
 *
 * This function writes the characters from the input string 'str' to the
 * specified file descriptor 'fd', allowing custom output destinations.
 * It returns the number of characters successfully written to the file
 * descriptor.
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written to the file descriptor.
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
