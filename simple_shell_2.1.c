#include "simple_shell.h"

/**
 * _myhistory - It displays the history list, one command by line, preceded
 *              with line numbers, starting with 0.
 * @information: The Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _myhistory(info_t *information)
{
	print_list(information->history);
	return (0);
}

/**
 * unset_alias - It sets alias to string
 * @information: The parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success or 1 on error
 */
int unset_alias(info_t *information, char *strng)
{
	char *bpz, mcz;
	int retn;

	bpz = _strchr(strng, '=');
	if (!bpz)
		return (1);
	mcz = *bpz;
	*bpz = 0;
	retn = delete_node_at_index(&(information->alias),
			get_node_index(information->alias, node_starts_with(information->alias,
					strng, -1)));
	*bpz = mcz;
	return (retn);
}

/**
 * set_alias - It sets alias to string
 * @information: The parameter struct
 * @strng: the string alias
 *
 * Return: Always 0 on success or 1 on error
 */
int set_alias(info_t *information, char *strng)
{
	char *bpz;

	bpz = _strchr(strng, '=');
	if (!bpz)
		return (1);
	if (!*++bpz)
		return (unset_alias(information, strng));

	unset_alias(information, strng);
	return (add_node_end(&(information->alias), strng, 0) == NULL);
}

/**
 * print_alias - It prints an alias string
 * @nodez: the alias node
 *
 * Return: Always 0 on success or 1 on error
 */
int print_alias(list_t *nodez)
{
	char *bpz = NULL, *maz = NULL;

	if (nodez)
	{
		bpz = _strchr(nodez->str, '=');
		for (maz = nodez->str; maz <= bpz; maz++)
			_putchar(*maz);
		_putchar('\'');
		_puts(bpz + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - It mimics the alias builtin
 * @information: The Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _myalias(info_t *information)
{
	int ai = 0;
	char *bpz = NULL;
	list_t *nodez = NULL;

	if (information->argc == 1)
	{
		nodez = information->alias;
		while (nodez)
		{
			print_alias(nodez);
			nodez = nodez->next;
		}
		return (0);
	}
	for (ai = 1; information->argv[ai]; ai++)
	{
		bpz = _strchr(information->argv[ai], '=');
		if (bpz)
			set_alias(information, information->argv[ai]);
		else
			print_alias(node_starts_with(information->alias,
						information->argv[ai], '='));
	}

	return (0);
}

