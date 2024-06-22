/*
 * File_name: error_1.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _erratoi - Convert a string to an integer with error handling.
 *
 * This function parses the input string and attempts to convert it into an
 * integer. If the string contains no numbers or if an error occurs during
 * conversion, it returns -1. Otherwise,
 * it returns the converted integer value.
 *
 * @s: The string to be converted.
 *
 * Return: The converted integer if successful, -1 on error.
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - Display a customized error message.
 *
 * @info: Pointer to the parameter & return info structure.
 * @estr: String containing a specified error type.
 *
 * This function is responsible for formatting and printing an
 * error message based on the provided error type (@estr) and
 * the context stored in the info structure (@info). It offers
 * detailed error feedback for better debugging.
 *
 * Return: 0 if no numbers are found in the string, the converted
 * number otherwise, or -1 on error.
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - Prints an integer (decimal, base 10)
 * to a specified file descriptor.
 *
 * @input: The integer to print.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - Transforms a long integer into a formatted string,
 * mimicking itoa.
 *
 * @num: The number to convert.
 * @base: The base for conversion (e.g., decimal, hexadecimal).
 * @flags: Flags indicating special formatting options.
 *
 * Return: A formatted string representing the converted number.
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - Elevates code, making it comment-free
 * @buf: Pointer to the code string to enhance
 *
 * Return: Always 0, as wisdom speaks through silence.
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
