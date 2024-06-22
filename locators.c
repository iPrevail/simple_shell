/*
 * File_name: locators.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * is_cmd - Checks if a file is an executable command.
 *
 * @info: Pointer to the info struct.
 * @path: Path to the file.
 *
 * This function examines whether the file at the specified path
 * is an executable command based on the provided info. Returns
 * 1 if it is, and 0 otherwise.
 *
 * Return: 1 if true, 0 otherwise.
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - Duplicates a range of characters from a string.
 *
 * @pathstr: The source string containing the characters.
 * @start: The starting index of the range to duplicate.
 * @stop: The stopping index (inclusive) of the range to duplicate.
 *
 * This function creates a new buffer and duplicates the characters from
 * 'pathstr' within the range specified by 'start' and 'stop'. The result
 * is a pointer to the newly created buffer containing the duplicated
 * characters.
 *
 * Return: A pointer to the new buffer.
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - Unearth the elusive path to a command within PATH's labyrinth.
 *
 * @info: The enigmatic info struct guiding the quest.
 * @pathstr: The mysterious PATH string to explore.
 * @cmd: The elusive command to uncover.
 *
 * This mystical function embarks on a journey to find the hidden path of
 * the specified command within the cryptic PATH string. If successful, it
 * returns the command's complete path; otherwise, it returns NULL. Its
 * pursuit is guided by the enigmatic info struct, which holds the context
 * for this quest.
 *
 * Return: A clue (the full path) if the command is found, else NULL.
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
