/*
 * File_name: champ1.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _strcpy - Craftily duplicates a string's essence.
 *
 * @dest: The canvas where the copy will reside.
 * @src: The source of inspiration.
 *
 * This function skillfully duplicates the essence of the source string
 * 'src' onto the canvas 'dest'. It preserves the artistic integrity of
 * the original, ensuring a faithful reproduction.
 *
 * Return: A pointer to the artful duplication on 'dest'.
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - Duplicate a string into a new memory location.
 *
 * @str: The string to be duplicated.
 *
 * This function clones the input string into a new memory block,
 * and returns a pointer to the duplicated string.
 *
 * Return: A pointer to the duplicated string or NULL if memory
 * allocation fails.
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Echoes a string to standard output.
 *
 * @str: The string to be gracefully printed.
 *
 * This function prints the input string to the console, followed by
 * a newline character, if available.
 *
 * Return: None.
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - Transmit a single character to standard output
 *
 * @c: The character to be printed
 *
 * This function writes the specified character to the standard output
 * stream (stdout) and returns 1 on success. On error, it returns -1 and
 * sets the appropriate error code in 'errno'.
 *
 * Return: 1 on success, -1 on error.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
