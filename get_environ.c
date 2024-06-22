/*
 * File_name: get_environ.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * get_environ - Creates a copy of the system environment variables.
 *
 * @info: Pointer to a structure holding function arguments (maintains
 *        prototype consistency).
 *
 * Return: Always returns 0.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable.
 *
 * @info: Structure with potential arguments (used to maintain
 *        a constant function prototype).
 * @var: The environment variable property to delete.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Bestows a new environment variable or tailors an existing one.
 *
 * @info: A struct holding possible arguments, preserving the constant
 *        function prototype.
 * @var: The ethereal string defining the environment variable.
 * @value: The mystical string embodying the variable's essence.
 *
 * Return: Always 0, signaling the harmonious coexistence of variables.
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
