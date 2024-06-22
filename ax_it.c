/*
 * File_name: ax_it.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _strncpy - Safely copy a portion of a string.
 *
 * @dest: Destination string to receive the copy.
 * @src: Source string to be copied from.
 * @n: Number of characters to copy.
 *
 * Return: Pointer to the modified destination string.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Merge two strings with finesse!
 *
 * @dest: The welcoming host string.
 * @src: The delightful guest string.
 * @n: The maximum number of bytes to mingle.
 *
 * Return: A harmonious blend of strings.
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Searches for a character in a string.
 *
 * This function scans a string for the first occurrence of the
 * specified character @c and returns a pointer to the memory
 * location where it's found within the string @s.
 *
 * @s: The string to be searched.
 * @c: The character to locate.
 *
 * Return: A pointer to the memory area in @s containing @c, or
 *         NULL if @c is not found.
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
