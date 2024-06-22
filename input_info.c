/*
 * File_name: input_info.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * clear_info - Wipes the slate clean for an info_t struct.
 *
 * This function resets all fields in the provided info_t struct to their
 * initial or default values, effectively initializing the struct for use.
 *
 * @info: A pointer to the info_t struct to be cleared.
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Infuse an info_t struct with essential data.
 *
 * @info: The blank canvas (struct address) awaiting life.
 * @av: A matrix of knowledge (argument vector).
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - Liberates resources within an info_t struct.
 *
 * @info: Pointer to the info_t struct to be managed.
 * @all: Boolean, true for freeing all fields, false for selective release.
 *
 * This function selectively frees resources within an info_t struct,
 * allowing granular control over memory management. When 'all' is true,
 * it releases all allocated fields; otherwise, it offers fine-grained
 * control for custom memory management.
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
