/*
 * File_name: link_list.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * list_len - Counts the number of nodes in a linked list.
 *
 * @h: Pointer to the first node in the list.
 *
 * This function calculates and returns the total number of nodes
 * in the provided linked list starting from the given pointer.
 *
 * Return: The size (length) of the linked list.
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - Extracts strings from a linked list into an array.
 *
 * @head: Pointer to the first node of the linked list.
 *
 * This function takes a linked list and extracts the 'str' field from each
 * node, storing them in an array of strings.
 * The resulting array is dynamically
 * allocated and should be freed after use to avoid memory leaks.
 *
 * Return: An array of strings containing the 'str'
 * values from the linked list.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - Traverse and print the elements of a list_t linked list.
 *
 * @h: Pointer to the first node of the list.
 *
 * This function iterates through the provided linked list, printing
 * each element, and returns the size of the list (number of nodes).
 *
 * Return: The size of the linked list.
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - Unearths a node adorned with
 * strings that commence in magic.
 *
 * @node: A compass to traverse the linked realm.
 * @prefix: The mystical incantation to initiate the journey.
 * @c: The enchanting follow-up character to solidify the connection.
 *
 * This function embarks on a quest within the linked realm, seeking a node
 * whose string begins with the enchanted 'prefix' and is followed by the
 * bewitching 'c'. Should the quest succeed, it returns the coveted node;
 * otherwise, it bestows the gift of null.
 *
 * Return: The mystical node that matched the incantation or null if none.
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - Seek the mystical index of a node in the grand list.
 *
 * @head: The enigmatic pointer to the list's head.
 * @node: The elusive pointer to the sought-after node.
 *
 * This function embarks on a quest through the linked list, starting from
 * the enigmatic head. It strives to unveil the elusive node's index within
 * the list. Should the node reveal itself, it shall disclose its index.
 * If the node remains hidden, a cryptic -1 is bestowed upon the seeker.
 *
 * Return: The index of the node, or -1 if it remains hidden.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
