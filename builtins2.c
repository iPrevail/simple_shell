/*
 * File_name: builtin2.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _myhistory - Display command history with line numbers.
 *
 * This function prints the command history stored in 'info' as a list of
 * commands, each preceded by a line number starting at 0.
 *
 * @info: Structure containing the command history and other information.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - Removes an alias from the system.
 *
 * This function takes an `info_t` parameter struct and a string `str`,
 * representing the alias to be unset. It removes the specified alias
 * from the system. If successful, it returns 0; otherwise, it returns 1
 * to indicate an error occurred.
 *
 * @info: Pointer to the parameter struct.
 * @str: The string alias to be unset.
 *
 * Return: 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Assigns an alias string to a parameter struct.
 *
 * This function sets an alias string within a parameter struct,
 * allowing for customized naming of parameters.
 *
 * @info: Pointer to the parameter struct.
 * @str: The string to be assigned as an alias.
 *
 * Return: 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Echoes the essence of an alias.
 *
 * @node: Pointer to the alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Emulates the 'alias' built-in command from 'man alias'.
 *
 * @info: Structure holding potential arguments to maintain
 *        a consistent function prototype.
 *
 * Return: Always returns 0.
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
