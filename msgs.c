/*
 * File_name: msgs.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * is_chain - Dances through the buffer,
 * seeking the rhythm of chain delimiters.
 *
 * @info: The conductor guiding this char-melody.
 * @buf: The musical notes (characters) to be played.
 * @p: The current note's sheet music position.
 *
 * This enchanting function, with the guidance of 'info,'
 * delicately checks if the
 * character at the given 'p' in 'buf'
 * plays the harmonious role of a chain delimiter.
 * It returns 1 if the character is in tune with the chain,
 * or 0 if it's out of sync.
 *
 * Return: 1 if the character dances as a chain delimiter, 0 otherwise.
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - Evaluates whether to continue
 * chaining based on prior status.
 *
 * @info: Pointer to the parameter struct.
 * @buf: Character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * This function assesses whether to proceed with chaining based on the
 * previous status, as indicated in the parameter struct. It operates on
 * the provided character buffer and current position, starting from 'i,'
 * and the total length 'len.'
 *
 * Return: Void.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Harmonizes tokenized string with defined aliases.
 *
 * @info: Pointer to the parameter struct.
 *
 * This function gracefully substitutes aliases in the tokenized string
 * using mappings stored in the parameter struct. When an alias is
 * successfully replaced, it returns 1; otherwise, it returns 0.
 *
 * Return: 1 if an alias is harmoniously replaced, 0 otherwise.
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replaces variables in the tokenized string.
 *
 * @info: Pointer to the parameter struct containing tokenized data.
 *
 * This function is responsible for processing a tokenized string and
 * replacing variables with their corresponding values as specified
 * in the 'info' parameter. It returns 1 if replacements were made,
 * or 0 if no replacements occurred.
 *
 * Return: 1 if variables were replaced, 0 otherwise.
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - Transform and rejuvenate a string.
 *
 * @old: Address of the aging string to be reborn.
 * @new: The vibrant, new string to replace the old one.
 *
 * Breathe new life into an old string by replacing it with a fresh,
 * dynamic one.
 * If the transformation is successful, it returns 1; otherwise, it returns 0.
 *
 * Return: 1 if the transformation is successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
