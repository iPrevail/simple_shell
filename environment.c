/*
 * File_name: environment.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * _myenv - Print the current environment variables.
 *
 * @info: A structure containing potential arguments, ensuring a consistent
 *        function prototype.
 *
 * This function prints the current environment variables to the standard
 * output. It takes an 'info_t' structure to maintain a uniform function
 * signature but doesn't use it for this operation.
 *
 * Return: Always returns 0.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - Retrieve the value of an environment variable.
 *
 * @info: Structure containing relevant program information.
 * @name: Name of the environment variable to retrieve.
 *
 * This function searches for the environment variable specified by @name
 * within the program's environment variables, which are stored in the
 * @info structure. If found, it returns the corresponding value.
 *
 * Return: The value of the environment variable if found, NULL if not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Set or modify an environment variable.
 *
 * This function allows you to initialize a new environment variable or
 * modify an existing one in a given context, as specified by the 'info'
 * structure. It provides a versatile way to manage environment variables.
 *
 * @info: Structure containing potential arguments and context information.
 *        It is used to maintain a consistent function prototype.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Eliminate an environment variable gracefully.
 *
 * This function takes an `info_t` structure as input, which may hold
 * additional arguments for further context. It gracefully removes
 * the specified environment variable, providing an elegant exit for
 * a piece of the program's environment.
 *
 * @info: Structure containing potential arguments and context.
 *
 * Return: Always returns 0, signaling successful execution.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - Create and populate an environment linked list.
 *
 * This function initializes and populates a linked list with environment
 * variables based on the provided `info` structure.
 *
 * @info: A structure containing potential arguments and other data needed
 *        for processing.
 *
 * Return: Always returns 0 to indicate successful execution.
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
