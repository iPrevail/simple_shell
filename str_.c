/*
 * File_name: str_.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _memset - Craftily imbues memory with a constant byte
 *
 * @s: The portal to the memory realm
 * @b: The mystical byte to infuse into @s
 * @n: The quantum of bytes to be enchanted
 *
 * Return: A parchment with coordinates to the memory realm
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - Liberates the memory occupied by an array of strings.
 *
 * @pp: A pointer to an array of strings.
 *
 * Description:
 * This function deallocates the memory used by an array of strings,
 * effectively freeing each individual string and then the array itself.
 * It is used to release resources when you no longer need the strings.
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Memory Maestro: Reshapes the orchestra.
 *
 * @ptr: A conductor's wand pointing to the old ensemble.
 * @old_size: The previous symphonic magnitude in bytes.
 * @new_size: The new grandiose size for the performance.
 *
 * Embrace the crescendo of change as this function reallocates a block
 * of memory, adapting your musical ensemble to a new score. The conductor's
 * wand guides the transformation, orchestrating memory passages.
 *
 * Return: A renewed pointer to the enduring masterpiece.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
