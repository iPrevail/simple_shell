/*
 * File_name: _truth.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */


#include "shell.h"

/**
 * interactive - Determines whether the shell is in interactive mode.
 *
 * @info: Pointer to the info struct.
 *
 * Return: 1 if interactive; 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter.
 *
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * This function determines whether the given character 'c' is a delimiter
 * by comparing it to the characters in the 'delim' string. If 'c' matches
 * any character in 'delim', the function returns 1 to indicate true;
 * otherwise, it returns 0 to indicate false.
 *
 * Return: 1 if 'c' is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - Unveils the alphabetic mystique of a char.
 *
 * @c: The enigmatic char to decipher.
 *
 * Return: 1 if c is a letter of the alphabet, 0 if it's an enigma.
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - String to integer conversion.
 *
 * @s: Str to convert.
 *
 * Return: 0 if no num, converted num otherwise.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
