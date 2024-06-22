/*
 * File_name: split.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * bfree - Emancipate memory, leaving a pristine void.
 *
 * @ptr: Pointer to the pointer of the captive memory.
 *
 * This function grants freedom to memory pointed to by the given pointer,
 * liberating it from captivity, and then it bestows upon the pointer itself
 * the gift of nothingness, a pristine NULL. A return of 1 signifies a
 * successful liberation; otherwise, it's 0, the memory remains bound.
 *
 * Return: 1 if memory was freed, 0 otherwise.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
