#include "simple_shell.h"

/**
 * add_node - adds a node to the start of a list
 * @headz: the address of pointer to head node
 * @strng: the strng field of node
 * @numz: the node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **headz, const char *strng, int numz)
{
	list_t *new_headz;

	if (!headz)
		return (NULL);
	new_headz = malloc(sizeof(list_t));
	if (!new_headz)
		return (NULL);
	_memset((void *)new_headz, 0, sizeof(list_t));
	new_headz->num = numz;
	if (strng)
	{
		new_headz->str = _strdup(strng);
		if (!new_headz->str)
		{
			free(new_headz);
			return (NULL);
		}
	}
	new_headz->next = *headz;
	*headz = new_headz;
	return (new_headz);
}

/**
 * add_node_end - adds a node to the end of the list
 * @headz: the address of pointer to head node
 * @strng: the strng field of node
 * @numz: the node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **headz, const char *strng, int numz)
{
	list_t *new_nodez, *nodez;

	if (!headz)
		return (NULL);

	nodez = *headz;
	new_nodez = malloc(sizeof(list_t));
	if (!new_nodez)
		return (NULL);
	_memset((void *)new_nodez, 0, sizeof(list_t));
	new_nodez->num = numz;
	if (strng)
	{
		new_nodez->str = _strdup(strng);
		if (!new_nodez->str)
		{
			free(new_nodez);
			return (NULL);
		}
	}
	if (nodez)
	{
		while (nodez->next)
			nodez = nodez->next;
		nodez->next = new_nodez;
	}
	else
		*headz = new_nodez;
	return (new_nodez);
}

/**
 * print_list_str - prints only the strng element of a list_t linked list
 * @zh: the pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *zh)
{
	size_t ai = 0;

	while (zh)
	{
		_puts(zh->str ? zh->str : "(nil)");
		_puts("\n");
		zh = zh->next;
		ai++;
	}
	return (ai);
}

/**
 * delete_node_at_index - deletes node at given index
 * @headz: the address of pointer to first node
 * @bindex: the index of node to delete
 *
 * Return: 0 on failure, 1 on success
 */
int delete_node_at_index(list_t **headz, unsigned int bindex)
{
	list_t *nodez, *prev_nodez;
	unsigned int ai = 0;

	if (!headz || !*headz)
		return (0);

	if (!bindex)
	{
		nodez = *headz;
		*headz = (*headz)->next;
		free(nodez->str);
		free(nodez);
		return (1);
	}
	nodez = *headz;
	while (nodez)
	{
		if (ai == bindex)
		{
			prev_nodez->next = nodez->next;
			free(nodez->str);
			free(nodez);
			return (1);
		}
		ai++;
		prev_nodez = nodez;
		nodez = nodez->next;
	}
	return (0);
}

/**
 * free_list - frees all the nodes of a list
 * @head_bptr: the address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_bptr)
{
	list_t *nodez, *next_nodez, *headz;

	if (!head_bptr || !*head_bptr)
		return;
	headz = *head_bptr;
	nodez = headz;
	while (nodez)
	{
		next_nodez = nodez->next;
		free(nodez->str);
		free(nodez);
		nodez = next_nodez;
	}
	*head_bptr = NULL;
}

