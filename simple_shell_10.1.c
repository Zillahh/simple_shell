#include "simple_shell.h"

/**
 * list_len - determines length of linked list
 * @zh: the pointer to first node
 *
 * Return: the size of list
 */
size_t list_len(const list_t *zh)
{
	size_t ai = 0;

	while (zh)
	{
		zh = zh->next;
		ai++;
	}
	return (ai);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @headz: the pointer to first node
 *
 * Return: the array of strings
 */
char **list_to_strings(list_t *headz)
{
	list_t *nodez = headz;
	size_t ai = list_len(headz), mj;
	char **strss;
	char *strng;

	if (!headz || !ai)
		return (NULL);
	strss = malloc(sizeof(char *) * (ai + 1));
	if (!strss)
		return (NULL);
	for (ai = 0; nodez; nodez = nodez->next, ai++)
	{
		strng = malloc(_strlen(nodez->str) + 1);
		if (!strng)
		{
			for (mj = 0; mj < ai; mj++)
				free(strss[mj]);
			free(strss);
			return (NULL);
		}

		strng = _strcpy(strng, nodez->str);
		strss[ai] = strng;
	}
	strss[ai] = NULL;
	return (strss);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @zh: the pointer to first node
 *
 * Return: the size of list
 */
size_t print_list(const list_t *zh)
{
	size_t ai = 0;

	while (zh)
	{
		_puts(convert_number(zh->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(zh->str ? zh->str : "(nil)");
		_puts("\n");
		zh = zh->next;
		ai++;
	}
	return (ai);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @nodez: the pointer to list head
 * @prefixz: the string to match
 * @mc: the next character after prefix to match
 *
 * Return: the matching node or null
 */
list_t *node_starts_with(list_t *nodez, char *prefixz, char mc)
{
	char *bp = NULL;

	while (nodez)
	{
		bp = starts_with(nodez->str, prefixz);
		if (bp && ((mc == -1) || (*bp == mc)))
			return (nodez);
		nodez = nodez->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @headz: the pointer to list head
 * @nodez: the pointer to the node
 *
 * Return: the index of node or -1
 */
ssize_t get_node_index(list_t *headz, list_t *nodez)
{
	size_t ai = 0;

	while (headz)
	{
		if (headz == nodez)
			return (ai);
		headz = headz->next;
		ai++;
	}
	return (-1);
}

