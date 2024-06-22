/*
 * File_name: link_list.c
 * Auth: Ephraim Eyram
 *       and Abigail Nyarkoh
 */

#include "shell.h"

/**
 * add_node - Sprouts a new node at the dawn of the list.
 *
 * @head: Address of the pointer to the list's head.
 * @str: String to nourish the new node's str field.
 * @num: A mystical number, a node index entwined with history.
 *
 * Return: The ever-expanding size of the list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - Weaves a tale of connection, appending a node
 * to the list's grand finale.
 *
 * @head: The mystical pointer guiding us to the head node.
 * @str: The poetic text to be inscribed on this new node.
 * @num: The historical marker, reminding us of this passage.
 *
 * Return: The majestic size of the list, now enriched by one.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Echoes the 'str' values from a list_t linked list.
 *
 * @h: Pointer to the first node of the list.
 *
 * This function traverses a linked list and prints the 'str' element
 * of each node. It returns the total number of nodes processed.
 *
 * Return: The size of the list.
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - Vanquish a node at a specified index.
 *
 * @head: Pointer to the first node.
 * @index: Index of the node to be obliterated.
 *
 * This function obliterates the node at the specified index, reducing
 * the list's size. It returns 1 on successful obliteration and 0 if the
 * node at the given index does not exist.
 *
 * Return: 1 on successful deletion, 0 otherwise.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - Liberates the memory of all nodes within a linked list.
 *
 * @head_ptr: A pointer to the address of the head node.
 *
 * This function deallocates the memory associated with each node in
 * the linked list, starting from the head. It ensures the complete
 * release of resources, making the list empty.
 *
 * Return: Void (no explicit return value).
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
