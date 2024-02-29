#include "simple_shell.h"

/**
 * _myenv - It prints the current environment
 * @information: The Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myenv(info_t *information)
{
	print_list_str(information->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @information: Structure containing potential arguments.
 * @bnamez: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *information, const char *bnamez)
{
	list_t *node = information->env;
	char *bpz;

	while (node)
	{
		bpz = starts_with(node->str, bnamez);
		if (bpz && *bpz)
			return (bpz);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - It Initialize a new environment variable,
 *             or modify an existing one
 * @information: The Structure containing potential arguments.
 *
 *  Return: Always 0
 */
int _mysetenv(info_t *information)
{
	if (information->argc != 3)
	{
		_eputs("Incorrect number of arguements kindly check again\n");
		return (1);
	}
	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -It  Remove an environment variable
 * @information: Structure containing potential arguments.
 *
 * Return: Always 0
 */
int _myunsetenv(info_t *information)
{
	int ai;

	if (information->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (ai = 1; ai <= information->argc; ai++)
		_unsetenv(information, information->argv[ai]);

	return (0);
}

/**
 * populate_env_list - It populates env linked list
 * @information: The Structure containing potential arguments.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *information)
{
	list_t *node = NULL;
	size_t ai;

	for (ai = 0; environ[ai]; ai++)
		add_node_end(&node, environ[ai], 0);
	information->env = node;
	return (0);
}

