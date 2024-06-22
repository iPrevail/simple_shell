/*
 * File_name: champ.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _strlen - Get the length of a string.
 *
 * @s: The string to measure.
 *
 * This function calculates and returns the length of the input string 's'.
 *
 * Return: The integer length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Lexicographically compares two strings.
 *
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * This function compares the strings @s1 and @s2 and returns:
 *  - A negative value if @s1 comes before @s2 in lexicographic order.
 *  - A positive value if @s1 comes after @s2 in lexicographic order.
 *  - Zero if @s1 and @s2 are equal.
 *
 * Return: The result of the comparison.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - Locate the start of needle in haystack.
 *
 * @haystack: The string to search within.
 * @needle: The substring to find at the start of haystack.
 *
 * This function checks if the haystack string starts with the needle
 * substring. If a match is found, it returns the address of the next
 * character in the haystack after the needle. If no match is found,
 * it returns NULL.
 *
 * Return: Address of the next character after needle or NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Harmoniously unites two strings, weaving their essence together.
 *
 * @dest: The canvas to blend with.
 * @src: The pigment to enhance the canvas.
 *
 * This mystical function artfully combines the source string into the
 * destination string, imbuing the resulting masterpiece with the essence
 * of both. The result is a harmonious union of characters, carefully
 * null-terminated to preserve its integrity.
 *
 * Return: A pointer to the merged masterpiece within the destination canvas.
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
